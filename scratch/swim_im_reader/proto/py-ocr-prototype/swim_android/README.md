# swim_android

Samsung Health swimming records in a calendar, with per-session interval and
IM/stroke evaluation. This is a separate Flutter app; `swim_ocr_android` and
the Kotlin read-test project are unchanged.

## What it does

- On the first launch, reads Exercise records from Samsung Health for the last
  365 days and stores them on the device. Later launches show the cached records
  immediately and automatically synchronize from the latest workout timestamp.
- Starts the calendar week on Sunday and ends on Saturday, with distinct weekend
  colors and monthly totals, training days, and weekly distance.
- Shows the number of sessions on each calendar day. Selecting a day expands
  its sessions in time order; tap a numbered session to evaluate that workout.
- Uses Samsung Health swimming intervals, stroke types, durations, pool length,
  distance, calorie, and heart-rate data with the existing swim analysis logic.
- Select a Samsung Health lap-list screenshot from the session card to analyze
  lap rest with on-device Korean text recognition. The image is processed in a
  temporary directory and is not retained. OCR lap counts and times are checked
  against Samsung Health intervals; review mismatches, edit lap rest seconds,
  or restore the original unannotated session from the evaluation screen.
- Samsung Health does not expose reliable per-lap start times. Without OCR,
  only a session-level rest estimate (session duration minus lap durations) is
  available. When OCR analysis is present, lap boundaries are accumulated from
  Samsung Health lap durations and OCR rest durations, starting at the session
  start time. The first lap start and the next lap after an OCR-confirmed rest
  of at least ten minutes are aligned only when the log shows a clear sequence
  of consecutive heart-rate rises. All other boundaries use accumulated lap
  durations and OCR-confirmed rests. Absolute log timestamps are matched
  against these lap windows and the chart uses the explicit session start/end
  time range.
  These per-lap heart rates are estimates, not exact lap-boundary measurements.
  Session average and maximum heart rates use Samsung Health's session metrics
  when available. The graph uses continuous line segments without point markers.
- Supports IM100 inference, suspected mismeasurement exclusion, fin-swimming
  tolerance, and a 50 m pool override. Interval details include stroke, pace,
  stroke count, and SWOLF, with stroke-colored charts and summaries.

## Core analysis boundaries

- `services/samsung_health_lap_ocr_reader.dart` owns screenshot orientation,
  tiling, text recognition, visual row ordering, and duplicate lap removal.
  Samsung Health screen-layout changes should be handled there first.
- `services/swim_rest_ocr_service.dart` connects image reading to the existing
  swim-text parser and reports screenshots that do not contain readable laps.
- `analysis/swim_rest_estimator.dart` compares OCR lap number, stroke, and time
  with Samsung Health data, extracts per-lap rests, and marks agreement below
  99% for review. Review-needed sessions can be corrected in the evaluation
  screen; 99% and higher is shown as confirmed.
- `analysis/swim_heart_rate_estimator.dart` aligns absolute log timestamps to
  accumulated lap and OCR-rest durations. It shifts a lap start only after a
  clear three-sample heart-rate rise at session start or following a rest of at
  least ten minutes.
- `theme/swim_colors.dart` centralizes stroke, weekend, analysis-status, and
  heart-rate-zone colors for light and dark themes.
- A saved birth year stays masked in analysis options and can be revealed with
  the visibility control when it needs to be checked or edited.

## Android setup

The Samsung Health Data SDK AAR is in `android/app/libs/`. Install Samsung
Health on a physical Samsung device and enable Samsung Health Data SDK developer
mode. The SDK does not support emulators.

From this directory:

```sh
flutter pub get
flutter run
```

Approve Exercise read access when prompted. An empty calendar means no swimming
Exercise sessions were returned for the requested period. Records without
interval data still show their available session-level duration, distance, and
calories.
When Samsung Health does not report pool length, the inherited analysis logic
uses its 25 m default and the evaluation screen marks distance/pace as estimated.
To analyze rest, select a session and tap its rest-analysis button, then choose
a screenshot that clearly shows the numbered lap list and rest durations.
The Android app packages ML Kit's Korean text-recognition model explicitly;
the Flutter plugin declares language-specific models as compile-only dependencies.
