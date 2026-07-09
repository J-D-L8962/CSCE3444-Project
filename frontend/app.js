function showPage(pageId) {
  const pages = document.querySelectorAll(".page");
  pages.forEach(page => page.classList.remove("active"));
  document.getElementById(pageId).classList.add("active");
}

function addAssignment() {
  const name = document.getElementById("assignmentName").value;
  const course = document.getElementById("courseName").value;
  const due = document.getElementById("dueDate").value;

  if (name === "" || course === "" || due === "") {
    alert("Please fill out all fields.");
    return;
  }

  const list = document.getElementById("assignmentList");
  const item = document.createElement("li");
  item.textContent = `${name} - ${course} - Due: ${due}`;
  list.appendChild(item);

  document.getElementById("assignmentName").value = "";
  document.getElementById("courseName").value = "";
  document.getElementById("dueDate").value = "";
}

function generatePlan() {
  const hours = document.getElementById("hours").value;
  const result = document.getElementById("planResult");

  if (hours === "") {
    alert("Enter available study hours.");
    return;
  }

  result.innerHTML = `
    <strong>Recommended Plan:</strong><br>
    • CSCE 3444: 1 hour<br>
    • Math review: 45 minutes<br>
    • Exam practice: 1 hour<br><br>
    Productivity suggestion: Start with the highest priority deadline.
  `;
}