document.addEventListener("DOMContentLoaded", () => {
    const makeBtn = document.getElementById("makeBtn");
    const buttonArea = document.getElementById("buttonArea");
  
    let count = 1;
  
    // makeBtn 을 누를 시:
    makeBtn.addEventListener("click", () => {
      // 버튼 생성
      const newButton = document.createElement("button");
      newButton.textContent = `삭제 버튼 ${count++}`;
  
      // 클릭 시 자기 자신 삭제
      newButton.addEventListener("click", () => {
        newButton.remove();  // 진짜로 DOM에서 사라짐
      });
  
      // 화면에 추가
      buttonArea.appendChild(newButton);
    });
  });
  