DROP TABLE IF EXISTS assignments;
DROP TABLE IF EXISTS users;

CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username TEXT UNIQUE NOT NULL,
    email TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    preferences TEXT
);

CREATE TABLE assignments (
    id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    title TEXT NOT NULL,
    course TEXT NOT NULL,
    due_date DATE NOT NULL,
    priority TEXT,
    notes TEXT
);

INSERT INTO users (username, email, password, preferences)
VALUES ('testuser', 'test@unt.edu', 'Password123!', 'Prefers evening study sessions');

INSERT INTO assignments (user_id, title, course, due_date, priority, notes)
VALUES
(1, 'Study Chapter 5', 'CSCE 3444', '2026-07-15', 'High', 'Focus on software requirements'),
(1, 'Complete Project Update', 'CSCE 3444', '2026-07-18', 'Medium', 'Update Trello and GitHub');