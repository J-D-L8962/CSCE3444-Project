const STORAGE_KEYS = {
  assignments: "smartStudyAssignments",
  exams: "smartStudyExams",
  profile: "smartStudyProfile",
  studyHours: "smartStudyHours"
};

let assignments = loadData(STORAGE_KEYS.assignments, [
  {
    id: 1,
    title: "Software Engineering Project",
    course: "CSCE 3444",
    dueDate: "2026-07-12",
    priority: "High",
    completed: false
  },
  {
    id: 2,
    title: "Linear Algebra Homework",
    course: "MATH 2418",
    dueDate: "2026-07-14",
    priority: "Medium",
    completed: false
  },
  {
    id: 3,
    title: "Assembly Practice",
    course: "COSC 2425",
    dueDate: "2026-07-10",
    priority: "Low",
    completed: true
  }
]);

let exams = loadData(STORAGE_KEYS.exams, [
  {
    id: 1,
    title: "CSCE 3444 Midterm",
    course: "CSCE 3444",
    date: "2026-07-15",
    time: "10:00",
    location: "Discovery Park"
  },
  {
    id: 2,
    title: "Linear Algebra Exam",
    course: "MATH 2418",
    date: "2026-07-18",
    time: "14:00",
    location: "Online"
  }
]);

let userProfile = loadData(STORAGE_KEYS.profile, {
  name: "Simran Ghimire",
  email: "student@my.unt.edu",
  major: "Computer Science",
  university: "University of North Texas",
  semester: "Summer 2026"
});

let totalStudyHours = Number(
  localStorage.getItem(STORAGE_KEYS.studyHours) || 6
);

document.addEventListener("DOMContentLoaded", initializeApp);

function initializeApp() {
  setCurrentDate();
  setDefaultStudyDate();
  fillProfileForm();
  renderEverything();
}

function loadData(key, fallback) {
  try {
    const savedValue = localStorage.getItem(key);

    if (!savedValue) {
      return fallback;
    }

    return JSON.parse(savedValue);
  } catch (error) {
    return fallback;
  }
}

function saveData() {
  localStorage.setItem(
    STORAGE_KEYS.assignments,
    JSON.stringify(assignments)
  );

  localStorage.setItem(
    STORAGE_KEYS.exams,
    JSON.stringify(exams)
  );

  localStorage.setItem(
    STORAGE_KEYS.profile,
    JSON.stringify(userProfile)
  );

  localStorage.setItem(
    STORAGE_KEYS.studyHours,
    String(totalStudyHours)
  );
}

/* AUTHENTICATION */

function showLoginForm() {
  document.getElementById("loginForm").classList.remove("hidden");
  document.getElementById("registerForm").classList.add("hidden");

  document.getElementById("loginTab").classList.add("active");
  document.getElementById("registerTab").classList.remove("active");

  clearAuthMessage();
}

function showRegisterForm() {
  document.getElementById("registerForm").classList.remove("hidden");
  document.getElementById("loginForm").classList.add("hidden");

  document.getElementById("registerTab").classList.add("active");
  document.getElementById("loginTab").classList.remove("active");

  clearAuthMessage();
}

function loginUser(event) {
  event.preventDefault();

  const email = document
    .getElementById("loginEmail")
    .value
    .trim();

  const password = document
    .getElementById("loginPassword")
    .value
    .trim();

  if (!email || !password) {
    showMessage("Please enter your email and password.", true);
    return;
  }

  openMainApplication();
}

function registerUser(event) {
  event.preventDefault();

  const name = document
    .getElementById("registerName")
    .value
    .trim();

  const email = document
    .getElementById("registerEmail")
    .value
    .trim();

  const password = document
    .getElementById("registerPassword")
    .value;

  const confirmPassword = document
    .getElementById("confirmPassword")
    .value;

  if (password !== confirmPassword) {
    showMessage("Passwords do not match.", true);
    return;
  }

  userProfile.name = name;
  userProfile.email = email;

  saveData();
  fillProfileForm();
  openMainApplication();
}

function openMainApplication() {
  document.getElementById("authScreen").classList.add("hidden");
  document.getElementById("mainApp").classList.remove("hidden");

  updateProfileDisplays();
  showPage("dashboardPage");
  renderEverything();
}

function logoutUser() {
  document.getElementById("mainApp").classList.add("hidden");
  document.getElementById("authScreen").classList.remove("hidden");

  document.getElementById("loginForm").reset();
  clearAuthMessage();
  showLoginForm();
}

function showMessage(message, isError = false) {
  const messageElement = document.getElementById("authMessage");

  messageElement.textContent = message;
  messageElement.style.color = isError ? "#b93030" : "#0b6b3a";
}

function clearAuthMessage() {
  const messageElement = document.getElementById("authMessage");

  if (messageElement) {
    messageElement.textContent = "";
  }
}

/* PAGE NAVIGATION */

function showPage(pageId, clickedButton = null) {
  document.querySelectorAll(".page").forEach((page) => {
    page.classList.remove("active-page");
  });

  const requestedPage = document.getElementById(pageId);

  if (!requestedPage) {
    return;
  }

  requestedPage.classList.add("active-page");

  document.querySelectorAll(".nav-item").forEach((button) => {
    button.classList.remove("active");
  });

  let navigationButton = clickedButton;

  if (!navigationButton) {
    navigationButton = document.querySelector(
      `.nav-item[data-page="${pageId}"]`
    );
  }

  if (navigationButton) {
    navigationButton.classList.add("active");
  }

  const pageTitles = {
    dashboardPage: "Dashboard",
    assignmentsPage: "Assignment Management",
    examsPage: "Exam Management",
    plannerPage: "AI Study Planner",
    progressPage: "Progress Tracking",
    profilePage: "User Profile"
  };

  document.getElementById("pageTitle").textContent =
    pageTitles[pageId] || "AI Smart Study Assistant";

  document.querySelector(".sidebar")?.classList.remove("open");

  if (pageId === "progressPage") {
    refreshProgress();
  }

  window.scrollTo({
    top: 0,
    behavior: "smooth"
  });
}

function openPageFromDashboard(pageId) {
  showPage(pageId);
}

function toggleSidebar() {
  document.querySelector(".sidebar")?.classList.toggle("open");
}

function showNotifications() {
  alert(
    "Reminders:\n\n" +
    "• Software Engineering Project is due soon.\n" +
    "• CSCE 3444 Midterm is approaching.\n" +
    "• Your AI study plan is ready."
  );
}

/* ASSIGNMENTS */

function toggleAssignmentForm() {
  const formCard = document.getElementById("assignmentFormCard");
  formCard.classList.toggle("hidden");

  if (!formCard.classList.contains("hidden")) {
    document.getElementById("assignmentFormTitle").textContent =
      "Add New Assignment";

    document.getElementById("editingAssignmentId").value = "";
    document.getElementById("assignmentForm").reset();
  }
}

function cancelAssignmentForm() {
  document.getElementById("assignmentForm").reset();
  document.getElementById("editingAssignmentId").value = "";
  document.getElementById("assignmentFormCard").classList.add("hidden");
}

function saveAssignment(event) {
  event.preventDefault();

  const editingId = Number(
    document.getElementById("editingAssignmentId").value
  );

  const assignmentData = {
    id: editingId || Date.now(),
    title: document.getElementById("assignmentTitle").value.trim(),
    course: document.getElementById("assignmentCourse").value.trim(),
    dueDate: document.getElementById("assignmentDueDate").value,
    priority: document.getElementById("assignmentPriority").value,
    completed: false
  };

  if (editingId) {
    const existingAssignment = assignments.find(
      (assignment) => assignment.id === editingId
    );

    assignmentData.completed =
      existingAssignment?.completed || false;

    assignments = assignments.map((assignment) =>
      assignment.id === editingId
        ? assignmentData
        : assignment
    );
  } else {
    assignments.push(assignmentData);
  }

  saveData();
  cancelAssignmentForm();
  renderEverything();
}

function editAssignment(id) {
  const assignment = assignments.find((item) => item.id === id);

  if (!assignment) {
    return;
  }

  document.getElementById("assignmentFormCard").classList.remove("hidden");
  document.getElementById("assignmentFormTitle").textContent =
    "Edit Assignment";

  document.getElementById("editingAssignmentId").value =
    assignment.id;

  document.getElementById("assignmentTitle").value =
    assignment.title;

  document.getElementById("assignmentCourse").value =
    assignment.course;

  document.getElementById("assignmentDueDate").value =
    assignment.dueDate;

  document.getElementById("assignmentPriority").value =
    assignment.priority;

  document.getElementById("assignmentFormCard").scrollIntoView({
    behavior: "smooth"
  });
}

function deleteAssignment(id) {
  const confirmed = confirm(
    "Are you sure you want to delete this assignment?"
  );

  if (!confirmed) {
    return;
  }

  assignments = assignments.filter(
    (assignment) => assignment.id !== id
  );

  saveData();
  renderEverything();
}

function toggleAssignmentComplete(id) {
  assignments = assignments.map((assignment) => {
    if (assignment.id === id) {
      return {
        ...assignment,
        completed: !assignment.completed
      };
    }

    return assignment;
  });

  saveData();
  renderEverything();
}

function renderAssignments() {
  const list = document.getElementById("assignmentList");

  if (!list) {
    return;
  }

  const searchValue =
    document.getElementById("assignmentSearch")?.value
      .trim()
      .toLowerCase() || "";

  const selectedFilter =
    document.getElementById("assignmentFilter")?.value || "All";

  const filteredAssignments = assignments.filter((assignment) => {
    const matchesSearch =
      assignment.title.toLowerCase().includes(searchValue) ||
      assignment.course.toLowerCase().includes(searchValue);

    let matchesFilter = true;

    if (["High", "Medium", "Low"].includes(selectedFilter)) {
      matchesFilter = assignment.priority === selectedFilter;
    }

    if (selectedFilter === "Completed") {
      matchesFilter = assignment.completed;
    }

    if (selectedFilter === "Pending") {
      matchesFilter = !assignment.completed;
    }

    return matchesSearch && matchesFilter;
  });

  list.innerHTML = "";

  filteredAssignments.forEach((assignment) => {
    const card = document.createElement("article");

    card.className =
      "task-card" +
      (assignment.completed ? " completed" : "");

    card.innerHTML = `
      <div class="task-card-main">
        <div class="task-icon">
          ${assignment.completed ? "✅" : "📝"}
        </div>

        <div>
          <h3>${escapeHtml(assignment.title)}</h3>

          <p>
            <strong>${escapeHtml(assignment.course)}</strong>
          </p>

          <p>
            Due: ${formatDate(assignment.dueDate)}
          </p>

          <span class="priority-badge priority-${assignment.priority.toLowerCase()}">
            ${assignment.priority} Priority
          </span>
        </div>
      </div>

      <div class="task-actions">
        <button
          class="action-btn complete-btn"
          onclick="toggleAssignmentComplete(${assignment.id})"
        >
          ${assignment.completed ? "Mark Pending" : "Mark Complete"}
        </button>

        <button
          class="action-btn edit-btn"
          onclick="editAssignment(${assignment.id})"
        >
          Edit
        </button>

        <button
          class="action-btn delete-btn"
          onclick="deleteAssignment(${assignment.id})"
        >
          Delete
        </button>
      </div>
    `;

    list.appendChild(card);
  });

  const emptyState = document.getElementById(
    "assignmentEmptyState"
  );

  emptyState?.classList.toggle(
    "hidden",
    filteredAssignments.length > 0
  );
}

/* EXAMS */

function toggleExamForm() {
  const formCard = document.getElementById("examFormCard");
  formCard.classList.toggle("hidden");

  if (!formCard.classList.contains("hidden")) {
    document.getElementById("examFormTitle").textContent =
      "Add New Exam";

    document.getElementById("editingExamId").value = "";
    document.getElementById("examForm").reset();
  }
}

function cancelExamForm() {
  document.getElementById("examForm").reset();
  document.getElementById("editingExamId").value = "";
  document.getElementById("examFormCard").classList.add("hidden");
}

function saveExam(event) {
  event.preventDefault();

  const editingId = Number(
    document.getElementById("editingExamId").value
  );

  const examData = {
    id: editingId || Date.now(),
    title: document.getElementById("examTitle").value.trim(),
    course: document.getElementById("examCourse").value.trim(),
    date: document.getElementById("examDate").value,
    time: document.getElementById("examTime").value,
    location: document.getElementById("examLocation").value.trim()
  };

  if (editingId) {
    exams = exams.map((exam) =>
      exam.id === editingId ? examData : exam
    );
  } else {
    exams.push(examData);
  }

  saveData();
  cancelExamForm();
  renderEverything();
}

function editExam(id) {
  const exam = exams.find((item) => item.id === id);

  if (!exam) {
    return;
  }

  document.getElementById("examFormCard").classList.remove("hidden");
  document.getElementById("examFormTitle").textContent =
    "Edit Exam";

  document.getElementById("editingExamId").value = exam.id;
  document.getElementById("examTitle").value = exam.title;
  document.getElementById("examCourse").value = exam.course;
  document.getElementById("examDate").value = exam.date;
  document.getElementById("examTime").value = exam.time;
  document.getElementById("examLocation").value = exam.location;

  document.getElementById("examFormCard").scrollIntoView({
    behavior: "smooth"
  });
}

function deleteExam(id) {
  const confirmed = confirm(
    "Are you sure you want to delete this exam?"
  );

  if (!confirmed) {
    return;
  }

  exams = exams.filter((exam) => exam.id !== id);

  saveData();
  renderEverything();
}

function renderExams() {
  const examList = document.getElementById("examList");

  if (!examList) {
    return;
  }

  examList.innerHTML = "";

  exams.forEach((exam) => {
    const card = document.createElement("article");
    card.className = "task-card";

    card.innerHTML = `
      <div class="task-card-main">
        <div class="task-icon">📚</div>

        <div>
          <h3>${escapeHtml(exam.title)}</h3>

          <p>
            <strong>${escapeHtml(exam.course)}</strong>
          </p>

          <p>Date: ${formatDate(exam.date)}</p>
          <p>Time: ${formatTime(exam.time)}</p>
          <p>Location: ${escapeHtml(exam.location)}</p>
        </div>
      </div>

      <div class="task-actions">
        <button
          class="action-btn edit-btn"
          onclick="editExam(${exam.id})"
        >
          Edit
        </button>

        <button
          class="action-btn delete-btn"
          onclick="deleteExam(${exam.id})"
        >
          Delete
        </button>
      </div>
    `;

    examList.appendChild(card);
  });

  document
    .getElementById("examEmptyState")
    ?.classList.toggle("hidden", exams.length > 0);
}

/* AI STUDY PLANNER */

function generateStudyPlan(event) {
  event.preventDefault();

  const hours = Number(
    document.getElementById("availableHours").value
  );

  const studyDate =
    document.getElementById("studyDate").value;

  const breakPreference = Number(
    document.getElementById("breakPreference").value
  );

  const studyGoal =
    document.getElementById("studyGoal").value.trim();

  if (!hours || hours < 1) {
    alert("Please enter at least one available study hour.");
    return;
  }

  totalStudyHours += hours;
  saveData();

  const pendingAssignments = assignments
    .filter((assignment) => !assignment.completed)
    .sort((first, second) => {
      const priorityOrder = {
        High: 1,
        Medium: 2,
        Low: 3
      };

      return (
        priorityOrder[first.priority] -
        priorityOrder[second.priority]
      );
    });

  const studyItems = [];

  pendingAssignments.forEach((assignment) => {
    studyItems.push({
      title: assignment.title,
      course: assignment.course,
      type: "Assignment"
    });
  });

  exams.forEach((exam) => {
    studyItems.push({
      title: `${exam.title} Review`,
      course: exam.course,
      type: "Exam Review"
    });
  });

  if (studyItems.length === 0) {
    studyItems.push({
      title: "General Course Review",
      course: "Academic Review",
      type: "Study Session"
    });
  }

  const totalMinutes = hours * 60;
  const sessionLength = Math.min(
    breakPreference,
    Math.max(25, Math.floor(totalMinutes / studyItems.length))
  );

  let currentMinutes = 9 * 60;
  let remainingMinutes = totalMinutes;

  const generatedSessions = [];

  let itemIndex = 0;

  while (remainingMinutes >= 25) {
    const item = studyItems[itemIndex % studyItems.length];
    const duration = Math.min(sessionLength, remainingMinutes);

    const startTime = minutesToClock(currentMinutes);
    const endTime = minutesToClock(currentMinutes + duration);

    generatedSessions.push({
      startTime,
      endTime,
      duration,
      item
    });

    currentMinutes += duration + 10;
    remainingMinutes -= duration;
    itemIndex += 1;
  }

  const result = document.getElementById("studyPlanResult");

  result.innerHTML = `
    <div class="plan-tip">
      <strong>AI Productivity Suggestion</strong><br>
      Start with the highest-priority deadline and use focused study
      sessions followed by short breaks.
      ${
        studyGoal
          ? `<br><br><strong>Your goal:</strong> ${escapeHtml(studyGoal)}`
          : ""
      }
    </div>

    <p>
      <strong>Plan date:</strong> ${formatDate(studyDate)}
    </p>

    ${generatedSessions
      .map(
        (session) => `
          <div class="plan-session">
            <div class="plan-time">
              ${session.startTime}–${session.endTime}
            </div>

            <div>
              <strong>${escapeHtml(session.item.title)}</strong>
              <p>
                ${escapeHtml(session.item.course)} ·
                ${session.duration} minutes ·
                ${session.item.type}
              </p>
            </div>
          </div>
        `
      )
      .join("")}
  `;

  renderEverything();
}

function clearStudyPlan() {
  document.getElementById("plannerForm").reset();
  setDefaultStudyDate();

  document.getElementById("studyPlanResult").innerHTML = `
    <div class="empty-plan">
      <div>🤖</div>
      <h3>Your study plan will appear here</h3>
      <p>
        Enter your study availability and let the AI assistant
        organize your schedule.
      </p>
    </div>
  `;
}

/* PROGRESS */

function refreshProgress() {
  const completedAssignments = assignments.filter(
    (assignment) => assignment.completed
  );

  const pendingAssignments = assignments.filter(
    (assignment) => !assignment.completed
  );

  const totalAssignments = assignments.length;

  const progressPercent =
    totalAssignments === 0
      ? 0
      : Math.round(
          (completedAssignments.length / totalAssignments) * 100
        );

  setText(
    "overallProgressPercent",
    `${progressPercent}%`
  );

  setText(
    "progressCompletedCount",
    completedAssignments.length
  );

  setText(
    "progressPendingCount",
    pendingAssignments.length
  );

  setText("progressStudyHours", totalStudyHours);
  setText("progressStreak", "5 days");

  const progressCircle =
    document.getElementById("progressCircle");

  if (progressCircle) {
    const degrees = Math.round(
      (progressPercent / 100) * 360
    );

    progressCircle.style.background = `
      conic-gradient(
        #0b6b3a 0deg ${degrees}deg,
        #e2e8e4 ${degrees}deg 360deg
      )
    `;
  }

  const message =
    progressPercent >= 80
      ? "Excellent work! You are almost finished."
      : progressPercent >= 50
        ? "You are making strong progress."
        : "You are making steady progress.";

  setText("progressMessage", message);

  renderProgressLists(
    completedAssignments,
    pendingAssignments
  );
}

function renderProgressLists(completed, pending) {
  renderSimpleAssignmentList(
    "completedAssignmentList",
    completed,
    "No assignments completed yet."
  );

  renderSimpleAssignmentList(
    "pendingAssignmentList",
    pending,
    "No pending assignments."
  );
}

function renderSimpleAssignmentList(
  containerId,
  list,
  emptyMessage
) {
  const container = document.getElementById(containerId);

  if (!container) {
    return;
  }

  if (list.length === 0) {
    container.innerHTML = `
      <div class="list-item">
        <p>${emptyMessage}</p>
      </div>
    `;

    return;
  }

  container.innerHTML = list
    .map(
      (assignment) => `
        <div class="list-item">
          <div class="list-item-main">
            <div class="list-icon">
              ${assignment.completed ? "✅" : "⏳"}
            </div>

            <div>
              <h4>${escapeHtml(assignment.title)}</h4>
              <p>
                ${escapeHtml(assignment.course)} ·
                ${formatDate(assignment.dueDate)}
              </p>
            </div>
          </div>

          <span class="priority-badge priority-${assignment.priority.toLowerCase()}">
            ${assignment.priority}
          </span>
        </div>
      `
    )
    .join("");
}

/* PROFILE */

function fillProfileForm() {
  setInputValue("profileName", userProfile.name);
  setInputValue("profileEmail", userProfile.email);
  setInputValue("profileMajor", userProfile.major);
  setInputValue("profileUniversity", userProfile.university);
  setInputValue("profileSemester", userProfile.semester);

  updateProfileDisplays();
}

function saveProfile(event) {
  event.preventDefault();

  userProfile = {
    name: document.getElementById("profileName").value.trim(),
    email: document.getElementById("profileEmail").value.trim(),
    major: document.getElementById("profileMajor").value.trim(),
    university: document
      .getElementById("profileUniversity")
      .value
      .trim(),
    semester: document
      .getElementById("profileSemester")
      .value
      .trim()
  };

  saveData();
  updateProfileDisplays();

  alert("Profile saved successfully.");
}

function updateProfileDisplays() {
  const firstName =
    userProfile.name.split(" ")[0] || "Student";

  setText("headerUserName", userProfile.name);
  setText("welcomeName", firstName);
  setText("profileDisplayName", userProfile.name);

  const initials = userProfile.name
    .split(" ")
    .filter(Boolean)
    .slice(0, 2)
    .map((namePart) => namePart[0].toUpperCase())
    .join("");

  document.querySelectorAll(".avatar, .large-avatar").forEach(
    (avatar) => {
      avatar.textContent = initials || "ST";
    }
  );
}

/* DASHBOARD */

function renderDashboard() {
  const completedAssignments = assignments.filter(
    (assignment) => assignment.completed
  );

  const pendingAssignments = assignments.filter(
    (assignment) => !assignment.completed
  );

  const totalAssignments = assignments.length;

  const progressPercent =
    totalAssignments === 0
      ? 0
      : Math.round(
          (completedAssignments.length / totalAssignments) * 100
        );

  setText(
    "pendingAssignmentCount",
    pendingAssignments.length
  );

  setText("upcomingExamCount", exams.length);

  setText(
    "completedTaskCount",
    completedAssignments.length
  );

  setText(
    "dashboardProgressText",
    `${progressPercent}%`
  );

  setText(
    "dashboardCompleted",
    completedAssignments.length
  );

  setText(
    "dashboardPending",
    pendingAssignments.length
  );

  setText("dashboardStudyHours", totalStudyHours);

  const progressBar =
    document.getElementById("dashboardProgressBar");

  if (progressBar) {
    progressBar.style.width = `${progressPercent}%`;
  }

  renderDashboardAssignments(pendingAssignments);
  renderDashboardExams();
  updateAiRecommendation(pendingAssignments);
}

function renderDashboardAssignments(pendingAssignments) {
  const container =
    document.getElementById("dashboardAssignments");

  if (!container) {
    return;
  }

  const assignmentPreview = pendingAssignments
    .slice()
    .sort(
      (first, second) =>
        new Date(first.dueDate) -
        new Date(second.dueDate)
    )
    .slice(0, 3);

  if (assignmentPreview.length === 0) {
    container.innerHTML = `
      <div class="list-item">
        <div class="list-item-main">
          <div class="list-icon">🎉</div>
          <div>
            <h4>All assignments completed</h4>
            <p>You have no pending assignments.</p>
          </div>
        </div>
      </div>
    `;

    return;
  }

  container.innerHTML = assignmentPreview
    .map(
      (assignment) => `
        <div class="list-item">
          <div class="list-item-main">
            <div class="list-icon">📝</div>

            <div>
              <h4>${escapeHtml(assignment.title)}</h4>
              <p>
                ${escapeHtml(assignment.course)} ·
                Due ${formatDate(assignment.dueDate)}
              </p>
            </div>
          </div>

          <span class="priority-badge priority-${assignment.priority.toLowerCase()}">
            ${assignment.priority}
          </span>
        </div>
      `
    )
    .join("");
}

function renderDashboardExams() {
  const container =
    document.getElementById("dashboardExams");

  if (!container) {
    return;
  }

  const examPreview = exams
    .slice()
    .sort(
      (first, second) =>
        new Date(first.date) - new Date(second.date)
    )
    .slice(0, 3);

  if (examPreview.length === 0) {
    container.innerHTML = `
      <div class="list-item">
        <p>No exams currently scheduled.</p>
      </div>
    `;

    return;
  }

  container.innerHTML = examPreview
    .map(
      (exam) => `
        <div class="list-item">
          <div class="list-item-main">
            <div class="list-icon">📚</div>

            <div>
              <h4>${escapeHtml(exam.title)}</h4>
              <p>
                ${formatDate(exam.date)} ·
                ${formatTime(exam.time)}
              </p>
            </div>
          </div>
        </div>
      `
    )
    .join("");
}

function updateAiRecommendation(pendingAssignments) {
  const recommendationElement =
    document.getElementById(
      "dashboardAiRecommendation"
    );

  if (!recommendationElement) {
    return;
  }

  const highPriorityAssignment =
    pendingAssignments.find(
      (assignment) => assignment.priority === "High"
    );

  if (highPriorityAssignment) {
    recommendationElement.textContent =
      `Start with "${highPriorityAssignment.title}" because it has ` +
      `high priority. Then spend 45 minutes reviewing your nearest exam.`;

    return;
  }

  if (pendingAssignments.length > 0) {
    recommendationElement.textContent =
      `Begin with "${pendingAssignments[0].title}" and complete one ` +
      `focused study session before taking a short break.`;

    return;
  }

  recommendationElement.textContent =
    "All current assignments are complete. Review for your next exam.";
}

/* GENERAL RENDERING */

function renderEverything() {
  renderAssignments();
  renderExams();
  renderDashboard();
  refreshProgress();
  updateProfileDisplays();
}

function setCurrentDate() {
  const dateElement = document.getElementById("currentDate");

  if (!dateElement) {
    return;
  }

  dateElement.textContent = new Date().toLocaleDateString(
    "en-US",
    {
      weekday: "long",
      month: "long",
      day: "numeric",
      year: "numeric"
    }
  );
}

function setDefaultStudyDate() {
  const studyDateInput =
    document.getElementById("studyDate");

  if (!studyDateInput || studyDateInput.value) {
    return;
  }

  const today = new Date();
  const localDate = new Date(
    today.getTime() -
      today.getTimezoneOffset() * 60000
  )
    .toISOString()
    .split("T")[0];

  studyDateInput.value = localDate;
}

/* HELPERS */

function setText(elementId, value) {
  const element = document.getElementById(elementId);

  if (element) {
    element.textContent = value;
  }
}

function setInputValue(elementId, value) {
  const element = document.getElementById(elementId);

  if (element) {
    element.value = value;
  }
}

function formatDate(dateValue) {
  if (!dateValue) {
    return "No date";
  }

  const date = new Date(`${dateValue}T00:00:00`);

  return date.toLocaleDateString("en-US", {
    month: "short",
    day: "numeric",
    year: "numeric"
  });
}

function formatTime(timeValue) {
  if (!timeValue) {
    return "No time";
  }

  const [hours, minutes] = timeValue.split(":").map(Number);

  return new Date(2000, 0, 1, hours, minutes).toLocaleTimeString(
    "en-US",
    {
      hour: "numeric",
      minute: "2-digit"
    }
  );
}

function minutesToClock(totalMinutes) {
  const hours = Math.floor(totalMinutes / 60) % 24;
  const minutes = totalMinutes % 60;

  return new Date(2000, 0, 1, hours, minutes).toLocaleTimeString(
    "en-US",
    {
      hour: "numeric",
      minute: "2-digit"
    }
  );
}

function escapeHtml(value) {
  return String(value)
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;")
    .replaceAll("'", "&#039;");
}