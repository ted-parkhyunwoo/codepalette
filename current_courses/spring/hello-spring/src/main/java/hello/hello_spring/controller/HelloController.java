package hello.hello_spring.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.ui.Model;

@Controller
public class HelloController {
    
    @GetMapping("hello")    // host/hello 를 열었을 시
    public String hello(Model model) {
        model.addAttribute("data", "hello!!");  // ${data} 는 hello!! 로 치환하라
        return "hello";     // templates/hello.html을 찾아서 렌더링 할것이란 뜻.
    }
}
