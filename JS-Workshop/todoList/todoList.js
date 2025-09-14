document.addEventListener("DOMContentLoaded", function() {
  const textBox = document.getElementById("textBox");
  const addButton = document.getElementById("addButton");
  const todoList = document.getElementById("todoList");

  addButton.addEventListener("click", function() {
    const taskText = textBox.value.trim();

    if (taskText === "") {
      return;
    }

    const listItem = document.createElement("li");
    listItem.classList.add("todoItem");

    const taskSpan = document.createElement("span");
    taskSpan.classList.add("todoText");
    taskSpan.innerHTML = taskText;

    const deleteButton = document.createElement("button");
    deleteButton.innerHTML = "Delete";
    deleteButton.addEventListener("click", function() {
      listItem.remove();
    });

    listItem.appendChild(taskSpan);
    listItem.appendChild(deleteButton);

    todoList.appendChild(listItem);

    textBox.value = "";
  });
});
