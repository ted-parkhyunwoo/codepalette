import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:shared_preferences/shared_preferences.dart';

import '../models/swim_health_session.dart';

class SwimSessionCache {
  const SwimSessionCache({
    required this.sessions,
    required this.lastWorkoutTime,
  });

  final List<SwimHealthSession> sessions;
  final DateTime? lastWorkoutTime;
}

class SamsungHealthService {
  static const _channel = MethodChannel('com.codepalette.swim_android/health');
  static const _cacheKey = 'swim_health_session_cache_v1';
  static const _heartRateDataVersion = 2;

  Future<SwimSessionCache> readCachedSessions() async {
    final preferences = await SharedPreferences.getInstance();
    return _decodeCache(preferences.getString(_cacheKey));
  }

  Future<SwimSessionCache> synchronizeSessions() async {
    final preferences = await SharedPreferences.getInstance();
    final encodedCache = preferences.getString(_cacheKey);
    final cached = _decodeCache(encodedCache);
    final cachedHeartRateDataVersion = _readHeartRateDataVersion(encodedCache);
    final lastWorkoutTime =
        cached.lastWorkoutTime ?? _latestStartTime(cached.sessions);
    final fetchedSessions = await _readSwimSessions(
      sinceTime: cachedHeartRateDataVersion < _heartRateDataVersion
          ? null
          : lastWorkoutTime,
    );
    final cachedByStart = {
      for (final session in cached.sessions)
        session.startTime.millisecondsSinceEpoch: session,
    };
    final merged =
        <int, SwimHealthSession>{
          ...cachedByStart,
          for (final session in fetchedSessions)
            session.startTime.millisecondsSinceEpoch: session.withRestAnalysis(
              cachedByStart[session.startTime.millisecondsSinceEpoch]
                  ?.restAnalysis,
            ),
        }.values.toList()..sort(
          (first, second) => first.startTime.compareTo(second.startTime),
        );
    final latestWorkoutTime = _latestStartTime(merged);
    final cache = SwimSessionCache(
      sessions: merged,
      lastWorkoutTime: latestWorkoutTime,
    );
    final saved = await preferences.setString(
      _cacheKey,
      jsonEncode({
        'heartRateDataVersion': _heartRateDataVersion,
        'lastWorkoutTimeMillis': latestWorkoutTime?.millisecondsSinceEpoch,
        'sessions': merged.map((session) => session.toMap()).toList(),
      }),
    );
    if (!saved) {
      throw StateError('삼성 헬스 기록을 기기에 저장하지 못했습니다.');
    }
    return cache;
  }

  Future<void> saveSession(SwimHealthSession updatedSession) async {
    final preferences = await SharedPreferences.getInstance();
    final encodedCache = preferences.getString(_cacheKey);
    final cached = _decodeCache(encodedCache);
    final heartRateDataVersion = _readHeartRateDataVersion(encodedCache);
    final updatedSessions = [
      for (final session in cached.sessions)
        if (session.startTime != updatedSession.startTime)
          session
        else
          updatedSession,
    ];
    if (!updatedSessions.any(
      (session) => session.startTime == updatedSession.startTime,
    )) {
      throw StateError('수정할 수영 세션이 저장된 기록에 없습니다.');
    }
    final saved = await preferences.setString(
      _cacheKey,
      jsonEncode({
        'heartRateDataVersion': heartRateDataVersion,
        'lastWorkoutTimeMillis': cached.lastWorkoutTime?.millisecondsSinceEpoch,
        'sessions': updatedSessions.map((session) => session.toMap()).toList(),
      }),
    );
    if (!saved) {
      throw StateError('휴식 분석 결과를 기기에 저장하지 못했습니다.');
    }
  }

  Future<List<SwimHealthSession>> _readSwimSessions({
    required DateTime? sinceTime,
  }) async {
    final response = await _channel.invokeListMethod<Object?>(
      'readSwimSessions',
      sinceTime == null
          ? null
          : {'sinceTimeMillis': sinceTime.millisecondsSinceEpoch},
    );
    if (response == null) {
      throw const FormatException('삼성 헬스에서 기록 목록을 받지 못했습니다.');
    }

    final sessions =
        response.map((value) {
          if (value is! Map) {
            throw const FormatException('삼성 헬스 기록 형식이 올바르지 않습니다.');
          }
          return SwimHealthSession.fromMap(Map<String, dynamic>.from(value));
        }).toList()..sort(
          (first, second) => first.startTime.compareTo(second.startTime),
        );
    return sessions;
  }

  SwimSessionCache _decodeCache(String? encoded) {
    if (encoded == null) {
      return const SwimSessionCache(sessions: [], lastWorkoutTime: null);
    }

    final decoded = jsonDecode(encoded);
    if (decoded is! Map<String, dynamic> || decoded['sessions'] is! List) {
      throw const FormatException('저장된 수영 기록 형식이 올바르지 않습니다.');
    }
    final sessions =
        (decoded['sessions'] as List).map((item) {
          if (item is! Map) {
            throw const FormatException('저장된 수영 기록 형식이 올바르지 않습니다.');
          }
          return SwimHealthSession.fromMap(Map<String, dynamic>.from(item));
        }).toList()..sort(
          (first, second) => first.startTime.compareTo(second.startTime),
        );
    final lastWorkoutMillis = decoded['lastWorkoutTimeMillis'];
    if (lastWorkoutMillis != null && lastWorkoutMillis is! num) {
      throw const FormatException('저장된 마지막 운동 시간이 올바르지 않습니다.');
    }
    return SwimSessionCache(
      sessions: sessions,
      lastWorkoutTime: lastWorkoutMillis == null
          ? _latestStartTime(sessions)
          : DateTime.fromMillisecondsSinceEpoch(lastWorkoutMillis.toInt()),
    );
  }

  int _readHeartRateDataVersion(String? encoded) {
    if (encoded == null) return 0;
    final decoded = jsonDecode(encoded);
    if (decoded is! Map<String, dynamic>) {
      throw const FormatException('저장된 수영 기록 형식이 올바르지 않습니다.');
    }
    final version = decoded['heartRateDataVersion'];
    if (version == null) return 0;
    if (version is! num || version < 0) {
      throw const FormatException('저장된 심박 데이터 버전이 올바르지 않습니다.');
    }
    return version.toInt();
  }

  DateTime? _latestStartTime(List<SwimHealthSession> sessions) {
    if (sessions.isEmpty) return null;
    return sessions
        .map((session) => session.startTime)
        .reduce((first, second) => first.isAfter(second) ? first : second);
  }
}
