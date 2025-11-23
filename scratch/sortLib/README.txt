
다음에 대해 서술한다.
   1. python 에서 c코드 사용 (so, dll로 컴파일된 c라이브러리 사용)
      1-1. ctypes
      1-2. cffi

   2. c, cpp에서 qsort.c를 불러와 컴파일 하는 여러가지 방법
      2-1. so, dll로 라이브러리 한 것을 사용
      2-2. object 파일로 컴파일하여 사용  (링크)
      2-3. 모든 소스를 한번에 컴파일


1. python 에서 c 코드 사용 (so, dll로 컴파일된 c라이브러리 사용)
   모든방법: cffi, ctypes, cython, pybind11
      cffi 방식과 ctypes 방식, cython(pyx 작성 후 빌드 필요), pybind11(c 소스코드 내 PYBIND11 관련 작성해야하고 컴파일도 다름)

   현재시도: cffi 와 ctypes
      cffi 방식은 새로접한 방식이라 qsort.py 외에도 cffi_quick_sort.py 로 디테일하게 따로 작성됨
      ctypes 방식은 qsort.py 에만 구현됨

   사용 전: libqsort.so 혹은 libqsort.dll 을 현재 디렉토리에 컴파일 후 테스트 할 것.

   차이점: 
      ctypes
         타입지정이 좀 까다로운편. C보다 복잡도 증가 (포인터가 배열의 주소인지, 값인지에 따라 명시해야 하는듯. 또한 ptr++ 혹은 배열주소 + 정수길이 사용시 까다로움)
         start_ptr 을 배열로 바로 할당할수 있으나 end_ptr 은 start_ptr + length 등으로 사용할 수 없음. ctypes.cast로 배열임을, 포인터로 사용할 것임을 캐스팅해야함
         참조자료형 외 기본자료형은 쉬운편인것 같음

      cffi는 c스타일에 가까움
         헤더파일 배포도 필요없이 내부에 헤더처럼 인터페이스를 정의하여 사용
         큰 크기의 배열과 파이썬 리스트간 언팩도 빠른편이고 속도도 ctypes에 비해 월등함.
         포인터 변수에 직접 정수길이를 대입하는 등 간편한 편  def qsort_cffi(py_list: list) -> None:   메서드 참고.
         단점으로 vscode등에서 타입오류표기되는 코드들이 있음. # type: ignore  처리하여 해제함.




2. main.c 와 main.cpp는 파이썬에서 c 라이브러리 사용하는 것 과는 관련 없는 파일들이며, 간단한 quick 벤치마킹이 구현됨
   
   설명:       커스텀 라이브러리 혹은 소스코드를 컴파일하는 다양한 방법에 대해 서술
   공통사항:   main.c 혹은 main.cpp 에게 이런 함수가 있다는 것을 알리기 위해 인터페이스 제공 -> h파일 작성하고 include 함 (#include "qsort.h")
   컴파일 주의:
               아래 설명에는 -o 파일명.out 혹은 exe이 생략됨.  
               -O3 혹은 -Ofast 등이 생략됨.

   경로 주의:
               코드가 매우 보기 불편하여 libqsort에 관한건 libqsort에 모두 넣었음. 
               따라서 아래 시도들의 경로 힌트를 적긴 했지만, 컴파일 시 변경해야 할 수 있음


   1. 라이브러리(so, dll)을 불러와 컴파일 시도
      라이브러리 컴파일
         gcc -fPIC -shared ./lib/qsort.c -o ./lib/libqsort.so

      메인소스 컴파일
         gcc main.c -L./lib -lqsort

         linux의 경우 라이브러리 위치 명시가 강제됨:              // 다른 환경에서도 가능하면 권장방법을 사용
            런타임에 라이브러리위치 명시하려면:
               gcc main.c -L./lib -lqsort -Wl,-rpath,./lib        // 권장
            gcc main.c -L./lib -lqsort 한 이후라면: 
               export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH     // 비추천
         windows의 경우 library 파일의 위치가 같은 디렉토리 내에 있도록 거의 강제되어, -Wl,-rpath,./lib 는 무효처리됨
            1. 임시 환경변수 수정
               export PATH="$PWD/lib:$PATH"        // git bash
               set PATH=%CD%\lib;%PATH%            // cmd
               $env:PATH = "$PWD\lib;" + $env:PATH // powershell

            2. 나머지 방법들도 많으나, 코드를 수정하는 방향이 많음. 가능하면 위 방법으로 하거나, 아래 object파일 링킹, 혹은 함께컴파일 권장

                  

   2. object파일로 같이 컴파일
      오브젝트 컴파일(바이너리화)
         gcc -c ./lib/qsort.c -o qsort.o

      메인소스 링킹
         gcc main.c qsort.o
      
      cpp 링킹    (추천)
         g++ main.c qsort.o
      

   3. 소스코드 동시 제공으로 컴파일
      gcc main.c ./lib/qsort.c
      g++ main.cpp ./lib/qsort.c       // 비추천. C코드를 cpp로 컴파일시 extern C가 필요할 수 있음.