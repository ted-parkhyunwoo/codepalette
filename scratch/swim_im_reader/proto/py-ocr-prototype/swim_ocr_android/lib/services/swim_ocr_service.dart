import 'dart:io';
import 'dart:math' as math;

import 'package:google_mlkit_text_recognition/google_mlkit_text_recognition.dart';
import 'package:image/image.dart' as img;

import '../swim_data.dart';

/// Performs on-device Korean OCR and converts recognized text into swim data.
///
/// Images are orientation-corrected, tiled when long, and processed locally.
/// Temporary image files are removed before this service returns.
class SwimOcrService {
  /// Reads and analyzes one image without storing the image or result persistently.
  Future<SwimAnalysis> analyze(File source) async {
    final recognizer = TextRecognizer(script: TextRecognitionScript.korean);
    Directory? tempDirectory;
    try {
      final bytes = await source.readAsBytes();
      final decoded = img.decodeImage(bytes);
      if (decoded == null) {
        throw const FormatException('이미지를 읽을 수 없습니다.');
      }

      final oriented = img.bakeOrientation(decoded);
      tempDirectory = await Directory.systemTemp.createTemp('swim_ocr_');
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
        final tileFile =
            File('${tempDirectory.path}/tile_${tileTexts.length}.jpg');
        await tileFile.writeAsBytes(img.encodeJpg(enlarged, quality: 95));

        final recognized = await recognizer.processImage(
          InputImage.fromFile(tileFile),
        );
        tileTexts.add(_readInVisualOrder(recognized));

        if (start + length >= axisLength) break;
        start += tileLength - overlap;
      }

      return analyzeSwimText(_combineOcrTiles(tileTexts));
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

  /// Reconstructs reading rows by grouping recognized lines with nearby y-coordinates.
  String _readInVisualOrder(RecognizedText recognized) {
    final lines = recognized.blocks
        .expand((block) => block.lines)
        .where((line) => line.text.trim().isNotEmpty)
        .map(
          (line) => _OcrVisualLine(
            line.text.trim(),
            line.boundingBox.left,
            line.boundingBox.top,
            line.boundingBox.height,
          ),
        )
        .toList()
      ..sort((a, b) => a.centerY.compareTo(b.centerY));
    final rows = <_OcrVisualRow>[];

    for (final line in lines) {
      _OcrVisualRow? closestRow;
      var closestDistance = double.infinity;
      for (final row in rows) {
        final overlap =
            math.min(row.bottom, line.bottom) - math.max(row.top, line.top);
        final overlapRatio =
            overlap / math.min(row.bottom - row.top, line.height);
        final centerDistance = (row.centerY - line.centerY).abs();
        final sameVisualRow = overlapRatio >= 0.35 ||
            centerDistance <=
                math.max(row.bottom - row.top, line.height) * 0.45;
        if (sameVisualRow && centerDistance < closestDistance) {
          closestRow = row;
          closestDistance = centerDistance;
        }
      }

      if (closestRow == null) {
        rows.add(_OcrVisualRow(line));
      } else {
        closestRow.add(line);
      }
    }

    rows.sort((a, b) => a.centerY.compareTo(b.centerY));
    return rows.map((row) {
      row.lines.sort((a, b) => a.left.compareTo(b.left));
      return row.lines.map((line) => line.text).join(' ');
    }).join('\n');
  }

  /// Joins image tiles and removes duplicate lap lines from their overlap.
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

/// Holds one recognized text line and its position within an OCR image tile.
class _OcrVisualLine {
  _OcrVisualLine(this.text, this.left, this.top, this.height);

  final String text;
  final double left;
  final double top;
  final double height;
  double get centerY => top + height / 2;
  double get bottom => top + height;
}

/// Groups OCR lines whose bounding boxes occupy the same visual row.
class _OcrVisualRow {
  _OcrVisualRow(_OcrVisualLine line)
      : lines = [line],
        top = line.top,
        bottom = line.bottom;

  final List<_OcrVisualLine> lines;
  double top;
  double bottom;
  double get centerY =>
      lines.map((line) => line.centerY).reduce((a, b) => a + b) / lines.length;

  void add(_OcrVisualLine line) {
    lines.add(line);
    top = math.min(top, line.top);
    bottom = math.max(bottom, line.bottom);
  }
}
