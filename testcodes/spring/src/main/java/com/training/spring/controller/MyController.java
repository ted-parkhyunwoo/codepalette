package com.training.spring.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestParam;


@Controller
public class MyController {
    
    @GetMapping("hello")
    public String hello(Model model) {
        model.addAttribute("data","Hello");
        return "hello";
    }

    @GetMapping("mvc")
    // RequestParam은 javaStr에 대한 설명. ?name="" 으로 받은 변수명을 javaStr에 넣겠다. 라는 뜻
    // 함수명은 자유. 어차피 프레임워크에서 맵핑이 호출되면 아래 함수를 알아서 부름.
    public String mvcTest(@RequestParam(value = "name", required = true) String javaStr, Model model) {
        // javaStr 는 윗단에서 ?name="" 로 저장되어있으며, 이것을 타임리프 템플릿 ${data} 로 다룰 것이란 뜻.
        model.addAttribute("data", javaStr);
        return "mvc";
    }

    // 여러가지 써보기 vars?name=ted&age=20
    // 값을 비우고 vars/ 로 접속시 null 로 표기됨. userAge가 int라면 문제됨.
    @GetMapping("vars")
    public String vars(@RequestParam(value = "name", required = false) String userName,
                       @RequestParam(value = "age", required = false) String userAge,
                       Model model) {
        System.out.println(userName + userAge);
        model.addAttribute("name", userName);
        model.addAttribute("age", userAge);
        return "vars";
    }

    // 여러가지 써보기 vars2/ted/20
    // @PathVariable 에 주의.
    // 여기선 userAge가 정수형(int) 임.
    @GetMapping("vars2/{name}/{age}")
    public String vars2(@PathVariable(value = "name", required = true) String userName,
                       @PathVariable(value = "age", required = true) int userAge,
                       Model model) {
        model.addAttribute("name", userName);
        model.addAttribute("age", userAge);
        return "vars";
    }


}
