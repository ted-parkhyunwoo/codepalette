# Samsung Health Read Test (Android)

Minimal Android app to verify whether **your own app** can request and read Samsung Health Exercise records while Samsung Health Data SDK developer mode is enabled.

## Important
- This project is a test harness, not a Flutter app.
- Samsung's SDK `.aar` is proprietary and is **not included** in this ZIP.
- Download Samsung Health Data SDK from: https://developer.samsung.com/health/data/overview.html
- Copy the SDK file `samsung-health-data-api-*.aar` into `app/libs/`.
- This app requests **read-only Exercise** permission. It does not write data.
- The sample reads the last 90 days of Exercise records and prints session type/duration/calories. It is not yet a swim-lap/stroke parser.

## Build / install
1. Extract the ZIP.
2. Download the SDK and copy its AAR into `app/libs/`.
3. Open this folder in Android Studio (JDK 17).
4. Sync Gradle and run on your physical Android phone. Samsung says its SDK does not support emulators.
5. Ensure Samsung Health is installed and its Data SDK developer mode is enabled.
6. Tap **Request permission and read exercises**, then approve the Samsung Health permission dialog.

## How to interpret
- A Samsung Health permission dialog followed by records means your app's own package can access Exercise data.
- An empty list means the read call returned no records for the requested date range; try a period when you recorded an exercise.
- An error is shown in the app. Share the exact error text to diagnose it.

## Official references
- SDK overview/download: https://developer.samsung.com/health/data/overview.html
- Samsung's Exercise read example: https://developer.samsung.com/health/data/migration-guide/exercise-app-example.html
