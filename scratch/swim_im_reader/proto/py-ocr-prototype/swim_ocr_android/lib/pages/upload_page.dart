import 'dart:io';

import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';

import '../pages/results_pages.dart';
import '../services/swim_ocr_service.dart';
import '../swim_data.dart';

Color _ink(BuildContext context) => Theme.of(context).colorScheme.onSurface;
Color _muted(BuildContext context) =>
    Theme.of(context).colorScheme.onSurfaceVariant;
Color _accent(BuildContext context) => Theme.of(context).colorScheme.primary;
Color _secondary(BuildContext context) =>
    Theme.of(context).colorScheme.tertiary;
Color _softSurface(BuildContext context) =>
    Theme.of(context).colorScheme.secondaryContainer;

/// Owns image selection, transient analysis state, and result navigation.
class UploadPage extends StatefulWidget {
  const UploadPage({super.key});

  @override
  State<UploadPage> createState() => _UploadPageState();
}

/// Coordinates the current photo workflow; nothing is persisted between runs.
class _UploadPageState extends State<UploadPage> {
  final _picker = ImagePicker();
  final _ocrService = SwimOcrService();
  File? _image;
  SwimAnalysis? _analysis;
  bool _isProcessing = false;
  String? _errorMessage;

  @override
  void initState() {
    super.initState();
    if (Platform.isAndroid) {
      _restoreLostImage();
    }
  }

  /// Opens the system photo picker and starts analysis for the chosen image.
  Future<void> _selectImage() async {
    try {
      final selected = await _picker.pickImage(
        source: ImageSource.gallery,
        imageQuality: 100,
      );
      if (selected == null || !mounted) return;

      await _analyzeImage(File(selected.path));
    } catch (error) {
      _showError(error);
    }
  }

  /// Recovers a gallery selection if Android recreated the app while picking.
  Future<void> _restoreLostImage() async {
    try {
      final response = await _picker.retrieveLostData();
      if (!mounted || response.isEmpty) return;

      final image = response.file;
      if (image == null) {
        _showError(
          response.exception ?? '선택한 사진을 복원하지 못했습니다. 다시 선택해 주세요.',
        );
        return;
      }

      await _analyzeImage(File(image.path));
    } catch (error) {
      _showError(error);
    }
  }

  /// Runs the local OCR service and updates transient on-screen state.
  Future<void> _analyzeImage(File image) async {
    setState(() {
      _image = image;
      _analysis = null;
      _errorMessage = null;
      _isProcessing = true;
    });

    try {
      final result = await _ocrService.analyze(image);
      if (!mounted) return;
      setState(() {
        _analysis = result;
        _isProcessing = false;
      });
    } catch (error) {
      _showError(error);
    }
  }

  /// Presents analysis and picker failures without hiding the underlying error.
  void _showError(Object error) {
    if (!mounted) return;
    setState(() {
      _isProcessing = false;
      _errorMessage = '이미지를 분석하지 못했습니다. 다시 시도해 주세요.\n$error';
    });
  }

  /// Opens the available result views for the current image analysis.
  void _openResults() {
    final analysis = _analysis;
    if (analysis == null) return;
    showModalBottomSheet<void>(
      context: context,
      showDragHandle: true,
      backgroundColor: Theme.of(context).colorScheme.surface,
      builder: (context) => SafeArea(
        child: Padding(
          padding: const EdgeInsets.fromLTRB(20, 4, 20, 24),
          child: Column(
            mainAxisSize: MainAxisSize.min,
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                '분석 결과 보기',
                style: TextStyle(
                  color: _ink(context),
                  fontSize: 21,
                  fontWeight: FontWeight.w800,
                ),
              ),
              const SizedBox(height: 8),
              Text(
                '확인할 기록을 선택하세요.',
                style: TextStyle(color: _muted(context)),
              ),
              const SizedBox(height: 14),
              _ResultChoice(
                icon: Icons.table_rows_rounded,
                title: '모든 기록',
                subtitle: '${analysis.records.length}개 랩 기록',
                onTap: () =>
                    _pushResult(context, AllRecordsPage(analysis: analysis)),
              ),
              _ResultChoice(
                icon: Icons.swap_vert_rounded,
                title: 'IM ${analysis.poolLengthMeters * 4} 찾기',
                subtitle: '${analysis.imRecords.length}개 IM 세션',
                onTap: () =>
                    _pushResult(context, ImEvaluationPage(analysis: analysis)),
              ),
              _ResultChoice(
                icon: Icons.insights_rounded,
                title: '영법별 기록평가',
                subtitle: '${analysis.strokeSummaries.length}개 영법 요약',
                onTap: () => _pushResult(
                  context,
                  StrokeEvaluationPage(analysis: analysis),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }

  /// Replaces the result chooser with the selected results page.
  void _pushResult(BuildContext context, Widget page) {
    Navigator.pop(context);
    Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => page));
  }

  @override
  Widget build(BuildContext context) {
    final analysis = _analysis;
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          '수영 기록 분석',
          style: TextStyle(fontWeight: FontWeight.w800),
        ),
      ),
      body: ListView(
        padding: const EdgeInsets.fromLTRB(20, 8, 20, 30),
        children: [
          const _WelcomeCard(),
          const SizedBox(height: 18),
          FilledButton.icon(
            onPressed: _isProcessing ? null : _selectImage,
            icon: const Icon(Icons.add_photo_alternate_outlined),
            label: Text(_image == null ? '기록 사진 업로드' : '다른 사진 선택'),
            style: FilledButton.styleFrom(
              minimumSize: const Size.fromHeight(56),
              backgroundColor: _accent(context),
              foregroundColor: Theme.of(context).colorScheme.onPrimary,
              textStyle: const TextStyle(
                fontSize: 16,
                fontWeight: FontWeight.w700,
              ),
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(16),
              ),
            ),
          ),
          if (_isProcessing) ...[
            const SizedBox(height: 22),
            const _ProcessingCard(),
          ],
          if (_errorMessage case final message?) ...[
            const SizedBox(height: 16),
            _ErrorCard(message: message),
          ],
          if (_image != null && !_isProcessing) ...[
            const SizedBox(height: 18),
            _UploadedImageCard(image: _image!),
          ],
          if (analysis != null && !_isProcessing) ...[
            const SizedBox(height: 14),
            _AnalysisSummary(analysis: analysis),
            const SizedBox(height: 14),
            FilledButton.icon(
              onPressed: _openResults,
              icon: const Icon(Icons.analytics_outlined),
              label: const Text('결과 보기'),
              style: FilledButton.styleFrom(
                minimumSize: const Size.fromHeight(56),
                backgroundColor: _secondary(context),
                foregroundColor: Theme.of(context).colorScheme.onTertiary,
                textStyle: const TextStyle(
                  fontSize: 16,
                  fontWeight: FontWeight.w800,
                ),
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(16),
                ),
              ),
            ),
          ],
        ],
      ),
    );
  }
}

/// Introduces the app and its single-photo analysis workflow.
class _WelcomeCard extends StatelessWidget {
  const _WelcomeCard();

  @override
  Widget build(BuildContext context) {
    final scheme = Theme.of(context).colorScheme;
    return Container(
      padding: const EdgeInsets.all(22),
      decoration: BoxDecoration(
        borderRadius: BorderRadius.circular(22),
        gradient: LinearGradient(
          colors: [scheme.primary, scheme.tertiary],
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Icon(Icons.pool_rounded, color: scheme.onPrimary, size: 31),
          const SizedBox(height: 18),
          Text(
            '수영 기록',
            style: TextStyle(
              color: scheme.onPrimary,
              fontSize: 24,
              height: 1.22,
              fontWeight: FontWeight.w800,
            ),
          ),
          SizedBox(height: 8),
          Text(
            'Samsung Health 기록 분석',
            style: TextStyle(
              color: scheme.onTertiary,
              height: 1.4,
              fontSize: 14,
            ),
          ),
        ],
      ),
    );
  }
}

/// Indicates that the offline image recognition task is still running.
class _ProcessingCard extends StatelessWidget {
  const _ProcessingCard();

  @override
  Widget build(BuildContext context) {
    return Card(
      child: Padding(
        padding: EdgeInsets.all(20),
        child: Row(
          children: [
            SizedBox(
              width: 23,
              height: 23,
              child: CircularProgressIndicator(strokeWidth: 2.5),
            ),
            SizedBox(width: 14),
            Expanded(child: Text('사진에서 기록을 읽는 중')),
          ],
        ),
      ),
    );
  }
}

/// Displays photo picker or OCR errors without obscuring their details.
class _ErrorCard extends StatelessWidget {
  const _ErrorCard({required this.message});

  final String message;

  @override
  Widget build(BuildContext context) {
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Row(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Icon(Icons.error_outline,
                color: Theme.of(context).colorScheme.error),
            const SizedBox(width: 12),
            Expanded(
              child: Text(
                message,
                style: TextStyle(
                  color: Theme.of(context).colorScheme.error,
                  height: 1.4,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

/// Shows a preview that opens the source image in a dedicated zoomable viewer.
class _UploadedImageCard extends StatelessWidget {
  const _UploadedImageCard({required this.image});

  final File image;

  void _openImage(BuildContext context) {
    Navigator.of(context).push(
      MaterialPageRoute<void>(
        builder: (_) => PhotoViewerPage(image: image),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Card(
      clipBehavior: Clip.antiAlias,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Padding(
            padding: const EdgeInsets.fromLTRB(16, 15, 16, 11),
            child: Text(
              '업로드한 사진',
              style: TextStyle(
                color: _ink(context),
                fontWeight: FontWeight.w700,
              ),
            ),
          ),
          InkWell(
            onTap: () => _openImage(context),
            child: Stack(
              alignment: Alignment.bottomRight,
              children: [
                ConstrainedBox(
                  constraints: const BoxConstraints(maxHeight: 230),
                  child: SizedBox(
                    width: double.infinity,
                    child: Image.file(
                      image,
                      fit: BoxFit.contain,
                      alignment: Alignment.center,
                    ),
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.all(10),
                  child: DecoratedBox(
                    decoration: BoxDecoration(
                      color: Colors.black54,
                      borderRadius: BorderRadius.circular(20),
                    ),
                    child: const Padding(
                      padding: EdgeInsets.all(8),
                      child: Icon(
                        Icons.zoom_in,
                        color: Colors.white,
                        size: 20,
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}

/// Fits the full photo to the available screen and supports pinch zoom/pan.
class PhotoViewerPage extends StatelessWidget {
  const PhotoViewerPage({required this.image, super.key});

  final File image;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.black,
      extendBodyBehindAppBar: true,
      appBar: AppBar(
        backgroundColor: Colors.black38,
        foregroundColor: Colors.white,
        title: const Text('사진 미리보기'),
      ),
      body: LayoutBuilder(
        builder: (context, constraints) {
          final imageCanvas = Size(
            constraints.maxWidth,
            constraints.maxHeight,
          );
          return Center(
            child: InteractiveViewer(
              constrained: false,
              boundaryMargin: const EdgeInsets.all(24),
              minScale: 1,
              maxScale: 8,
              child: SizedBox.fromSize(
                size: imageCanvas,
                child: Image.file(
                  image,
                  fit: BoxFit.contain,
                  filterQuality: FilterQuality.high,
                ),
              ),
            ),
          );
        },
      ),
    );
  }
}

/// Summarizes the key counts and distance for the uploaded activity.
class _AnalysisSummary extends StatelessWidget {
  const _AnalysisSummary({required this.analysis});

  final SwimAnalysis analysis;

  @override
  Widget build(BuildContext context) {
    final scheme = Theme.of(context).colorScheme;
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(17),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                Icon(Icons.check_circle, color: scheme.tertiary, size: 20),
                const SizedBox(width: 8),
                Text(
                  '분석 완료',
                  style: TextStyle(
                    color: scheme.onSurface,
                    fontSize: 16,
                    fontWeight: FontWeight.w800,
                  ),
                ),
              ],
            ),
            const SizedBox(height: 14),
            Row(
              children: [
                _Metric(label: '랩 기록', value: '${analysis.records.length}'),
                _Metric(label: '총 거리', value: '${_totalDistance(analysis)}m'),
                _Metric(label: 'IM 세션', value: '${analysis.imRecords.length}'),
              ],
            ),
            if (analysis.records.isEmpty) ...[
              const SizedBox(height: 12),
              Text(
                '인식된 기록 없음',
                style: TextStyle(color: scheme.onSurfaceVariant, fontSize: 13),
              ),
            ],
          ],
        ),
      ),
    );
  }

  int _totalDistance(SwimAnalysis analysis) => analysis.totalDistanceMeters;
}

/// Displays one label/value pair in the home analysis summary.
class _Metric extends StatelessWidget {
  const _Metric({required this.label, required this.value});

  final String label;
  final String value;

  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            label,
            style: TextStyle(
              color: _muted(context),
              fontSize: 12,
            ),
          ),
          const SizedBox(height: 3),
          Text(
            value,
            style: TextStyle(
              color: _ink(context),
              fontSize: 19,
              fontWeight: FontWeight.w800,
            ),
          ),
        ],
      ),
    );
  }
}

/// Provides a single entry point to one analysis result view.
class _ResultChoice extends StatelessWidget {
  const _ResultChoice({
    required this.icon,
    required this.title,
    required this.subtitle,
    required this.onTap,
  });

  final IconData icon;
  final String title;
  final String subtitle;
  final VoidCallback onTap;

  @override
  Widget build(BuildContext context) {
    return ListTile(
      contentPadding: const EdgeInsets.symmetric(horizontal: 6, vertical: 3),
      leading: CircleAvatar(
        backgroundColor: _softSurface(context),
        foregroundColor: _accent(context),
        child: Icon(icon),
      ),
      title: Text(
        title,
        style: TextStyle(color: _ink(context), fontWeight: FontWeight.w700),
      ),
      subtitle: Text(subtitle),
      trailing: const Icon(Icons.chevron_right_rounded),
      onTap: onTap,
    );
  }
}
