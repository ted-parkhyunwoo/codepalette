# Swim OCR Android

Samsung Health 수영 기록 사진을 선택해 기기에서 OCR과 기록 분석을 수행하는 Flutter Android 앱입니다. 계정, 네트워크, 서버, DB, 캘린더, 저장된 결과가 필요하지 않습니다. 앱은 선택한 사진을 현재 실행 중에만 분석합니다.

## 실행

Flutter SDK와 Android SDK가 설치된 환경에서 실행합니다.

```bash
flutter pub get
flutter run
```

사진을 업로드하면 원본 방향을 반영하고, 긴 이미지는 겹치는 구간으로 나눠 확대 인식합니다. 인식된 줄은 화면 좌표 기준으로 읽기 순서에 맞게 정렬하고, 겹치는 구간의 중복 랩 번호는 한 번만 집계합니다. `구간(25m)` 또는 `구간(50m)`을 기준으로 랩과 IM 거리를 계산합니다. 결과에는 전체 랩, IM 100m/200m, 영법별 기록 평가가 있습니다. 앱은 기기 다크/라이트 모드를 따릅니다. Android에서 사진 선택 중 앱 프로세스가 종료되어도 선택 결과를 복원합니다.

업로드한 사진을 누르면 화면에 맞춰 전체 사진을 표시하고 확대·이동할 수 있습니다. 결과 표는 화면 폭과 값 길이에 맞춰 열 너비를 조정하고, 가로 스크롤이 가능한 경우 안내와 스크롤 막대를 표시합니다. IM 평가에는 접·배, 배·평, 평·자 사이 휴식만 포함합니다.

## 코드 구성

- `lib/main.dart`: 앱 시작 및 시스템 테마 연결
- `lib/app_theme.dart`: 라이트/다크 디자인 토큰
- `lib/pages/upload_page.dart`: 사진 선택, 일회성 분석 상태, 전체 사진 보기
- `lib/pages/results_pages.dart`: 전체 기록, IM, 영법별 결과와 표/차트
- `lib/services/swim_ocr_service.dart`: 오프라인 이미지 전처리, ML Kit OCR, 읽기 순서 정렬
- `lib/swim_data.dart`: 기록 모델, 파싱, 거리·IM·영법별 계산

## 검증

```bash
flutter analyze
flutter test
flutter build apk --debug
```
