package hello.hello_spring.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;


@Controller
public class HelloController {
    
    @GetMapping("hello")    // host/hello 를 열었을 시
    public String hello(Model model) {
        model.addAttribute("data", "hello!!");  // ${data} 는 hello!! 로 치환하라
        return "hello";     // templates/hello.html을 찾아서 렌더링 할것이란 뜻.
    }

    // $HOST/hello-mvc?name=ted 라는 방식으로 매개변수를 전달 (http-get)
    @GetMapping("hello-mvc")
    // value="name" 으로 http-get으로 받는 매개변수를 ?name= 으로 명시할 수 있다. @RequestParam("name") 으로 간추릴 수 있음.
    public String getMethodName(@RequestParam(value = "name", required = false) String name, Model model) {     // RequestParam(안에 기본 요구를 false를 설정할수 있다. -이럴땐 null처리)
        //! +@ 매개변수(?name=xx 가 없는) /hello-mvc도 열기위해. name.equal(null) 은 안됨. java.util.Objects.equals(name, null) 널비교는 이런식으로 함.
        if (java.util.Objects.equals(name, null)) name = "user!";       
        model.addAttribute("name", name);       // hello-mvc?name=이름 으로 입력받은 "이름" string을 "name"으로 전달하며, "name" 은 hello-template 에서 ${name} 으로 쓰임
        return "hello-template";
    }
    

    // API 방식 기초(XML방식. 일일히 코드안에 태그를 열고닫고 해야함. 최근엔 실제로 쓰일 일은 없음.)
    @GetMapping("hello-string")
    @ResponseBody       //! html의 body에 직접 넣어주겠다. (템플릿엔진을 넣지 않음: view resolver에게 넘기지 않음. httpMessageConverter 로 넘김. )
    //! httpmessageConverter는 StringConverter 혹은 JsonConverter 로 호출됨(문자열이냐 객체냐 에 따라 결정)
    // 문자열 : StringConverter (StringHttpMessageConverter)
    public String getMethodName(@RequestParam("name") String name) {
        return "hello " + name;     // body에 "hello " + name 이 그대로 대체되어버림.
    }
    
    //! API방식 - key:value json으로 리턴. e.g) hello-api?name=ted  ->  {"name":"ted"}
    // 객체처리 : JsonConverter (MappingJackson2HttpMessageConverter)
    // 굳이 원한다면 XML로 accept 처리하면(HTML 헤더에 headers: {'Accept': 'application/xml'}  <script>문으로 js 에서 처리) JsonConverter가 아닌 XMLConverter가 자동 호출된다 함
    @GetMapping("hello-api")
    @ResponseBody
    public Hello helloApi(@RequestParam("name") String name) {
       Hello hello = new Hello();
       hello.setName(name);
       return hello;                // 데이터 객체를 넘기면 body에 json방식으로 대체됨(구조체방식: java에선 데이터클래스 혹은 "데이터 전송객체" 방식)
    }

    // "java bean jackson" 와 "jackson bean" 혹은 "java bean 규약과 jacson 라이브러리의 관계" 로 불림. getter setter라고도 함. 프로퍼티 접근방식이라고도 함
    // getter setter의 규칙을 이용해 getName() -> name 혹은 isPossible() -> possible 과 같은 방식으로 자동 추론됨.
    //! +@ flask에서는 객체의 내장멤버메서드로 to_dict() 형식으로 직접 구현하여 dictionary를 리턴하면 자동으로 jsonify 됨. 혹은 데이터클래스를 asdict(객체)
    static class Hello {
        private String name;
        public String getName() { return this.name; }
        public void setName(String name) { this.name = name; }
    }
    


}
