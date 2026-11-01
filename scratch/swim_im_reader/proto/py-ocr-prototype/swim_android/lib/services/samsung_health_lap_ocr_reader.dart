import 'dart:io';
import 'dart:math' as math;

import 'package:google_mlkit_text_recognition/google_mlkit_text_recognition.dart';
import 'package:image/image.dart' as img;

/// 삼성 헬스 랩 목록 캡처에서 화면에 보이는 순서의 텍스트를 추출
///
/// 이미지 방향, 분할, OCR 읽기 순서, 타일 중복 제거는 UI 구조 변화에 맞춰 이 파일에서 조정
class SamsungHealthLapOcrReader {
  Future<String> read(File source) async {
    final recognizer = TextRecognizer(script: TextRecognitionScript.korean);
    Directory? tempDirectory;
    try {
      final decoded = img.decodeImage(await source.readAsBytes());
      if (decoded == null) {
        throw const FormatException('이미지를 읽을 수 없습니다.');
      }

      final oriented = img.bakeOrientation(decoded);
      tempDirectory = await Directory.systemTemp.createTemp('swim_rest_ocr_');
      final axisLength = math.max(oriented.width, oriented.height);
      const tileLength = 1800;
      const overlap = 160;
      final splitVertically = oriented.height >= oriented.width;
      final tileTexts = <String>[];
      var start = 0;
      while (start < axisLength) {
        final length = math.min(tileLength, axisLength - start);
        final tile = img.copyCrop(
          oriented,
          x: splitVertically ? 0 : start,
          y: splitVertically ? start : 0,
          width: splitVertically ? oriented.width : length,
          height: splitVertically ? length : oriented.height,
        );
        final grayscale = img.grayscale(tile);
        final enlarged = img.copyResize(
          grayscale,
          width: grayscale.width * 3 ~/ 2,
          height: grayscale.height * 3 ~/ 2,
          interpolation: img.Interpolation.cubic,
        );
        final tileFile = File(
          '${tempDirectory.path}/tile_${tileTexts.length}.jpg',
        );
        await tileFile.writeAsBytes(img.encodeJpg(enlarged, quality: 95));
        final recognized = await recognizer.processImage(
          InputImage.fromFile(tileFile),
        );
        tileTexts.add(_readInVisualOrder(recognized));
        if (start + length >= axisLength) break;
        start += tileLength - overlap;
      }
      return _combineOcrTiles(tileTexts);
    } finally {
      try {
        await recognizer.close();
      } finally {
        if (tempDirectory != null && await tempDirectory.exists()) {
          await tempDirectory.delete(recursive: true);
        }
      }
    }
  }

  String _readInVisualOrder(RecognizedText recognized) {
    final lines =
        recognized.blocks
            .expand((block) => block.lines)
            .where((line) => line.text.trim().isNotEmpty)
            .map(
              (line) => _VisualLine(
                line.text.trim(),
                line.boundingBox.left,
                line.boundingBox.top,
                line.boundingBox.height,
              ),
            )
            .toList()
          ..sort((first, second) => first.centerY.compareTo(second.centerY));
    final rows = <_VisualRow>[];

    for (final line in lines) {
      _VisualRow? closestRow;
      var closestDistance = double.infinity;
      for (final row in rows) {
        final overlap =
            math.min(row.bottom, line.bottom) - math.max(row.top, line.top);
        final overlapRatio =
            overlap / math.min(row.bottom - row.top, line.height);
        final centerDistance = (row.centerY - line.centerY).abs();
        final sameVisualRow =
            overlapRatio >= 0.35 ||
            centerDistance <=
                math.max(row.bottom - row.top, line.height) * 0.45;
        if (sameVisualRow && centerDistance < closestDistance) {
          closestRow = row;
          closestDistance = centerDistance;
        }
      }
      if (closestRow == null) {
        rows.add(_VisualRow(line));
      } else {
        closestRow.add(line);
      }
    }

    rows.sort((first, second) => first.centerY.compareTo(second.centerY));
    return rows
        .map((row) {
          row.lines.sort((first, second) => first.left.compareTo(second.left));
          return row.lines.map((line) => line.text).join(' ');
        })
        .join('\n');
  }

  String _combineOcrTiles(List<String> tileTexts) {
    final combinedLines = <String>[];
    final seenLapNumbers = <int>{};
    final lapPrefix = RegExp(r'^(\d+)\b');
    for (final text in tileTexts) {
      for (final rawLine in text.split(RegExp(r'\r?\n'))) {
        final line = rawLine.trim();
        if (line.isEmpty) continue;
        final match = lapPrefix.firstMatch(line);
        if (match != null && !seenLapNumbers.add(int.parse(match.group(1)!))) {
          continue;
        }
        combinedLines.add(line);
      }
    }
    return combinedLines.join('\n');
  }
}

class _VisualLine {
  _VisualLine(this.text, this.left, this.top, this.height);

  final String text;
  final double left;
  final double top;
  final double height;
  double get centerY => top + height / 2;
  double get bottom => top + height;
}

class _VisualRow {
  _VisualRow(_VisualLine line)
    : lines = [line],
      top = line.top,
      bottom = line.bottom;

  final List<_VisualLine> lines;
  double top;
  double bottom;
  double get centerY =>
      lines
          .map((line) => line.centerY)
          .reduce((first, second) => first + second) /
      lines.length;

  void add(_VisualLine line) {
    lines.add(line);
    top = math.min(top, line.top);
    bottom = math.max(bottom, line.bottom);
  }
}
