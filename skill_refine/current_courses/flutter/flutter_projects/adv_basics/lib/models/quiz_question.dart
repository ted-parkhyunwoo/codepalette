class QuizQuestion {
  // data클래스의 퀴즈 답변을 그저 뒤섞는 용도의 클래스
  final String text;
  final List<String> answers;

  const QuizQuestion(this.text, this.answers);

  //! dart 문법: result_screen에서처럼 이것도 getter로 속성화 처리
  List<String> get shuffledAnswers {
    final shuffledList = List.of(answers);
    shuffledList.shuffle();
    return shuffledList;
  }
}
