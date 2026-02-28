<div align="center">

# 🍝 philosophers

**The Dining Philosophers Problem. Threads, mutexes, and the art of not starving.**

![C](https://img.shields.io/badge/language-C-blue?style=for-the-badge&logo=c)
![42](https://img.shields.io/badge/school-42-black?style=for-the-badge)
![Score](https://img.shields.io/badge/score-100%2F100-brightgreen?style=for-the-badge)

</div>

---

## 🧠 What is philosophers?

A classic concurrency problem: N philosophers sit at a round table. Between each pair is a fork. A philosopher needs **two forks** to eat. After eating, they think. If they don't eat in time, they die.

Your mission: prevent deadlocks, prevent starvation, and keep everyone alive using **POSIX threads** and **mutexes**.

---

## 🍴 The Rules

- Each philosopher is a **thread**
- Each fork is a **mutex**
- A philosopher cycles: **thinking → hungry → eating → thinking**
- If a philosopher doesn't start eating within `time_to_die` ms since their last meal → they die
- Simulation stops when a philosopher dies, or when all have eaten `n` times (if specified)

---

## 🚀 Usage

```bash
git clone https://github.com/Houdaifa1/philosophers
cd philosophers
make
```

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [times_must_eat]
```

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Max ms without eating before death |
| `time_to_eat` | Time (ms) to eat |
| `time_to_sleep` | Time (ms) to sleep |
| `[times_must_eat]` | Optional: stop after each philo eats this many times |

**Examples:**

```bash
./philo 5 800 200 200         # Classic setup, nobody should die
./philo 5 800 200 200 7       # Stops after each philosopher eats 7 times
./philo 4 310 200 100         # Edge case: tight timing
./philo 1 800 200 200         # One philosopher — must die
```

---

## 🔧 Build

```bash
make        # Compile
make clean  # Remove objects
make fclean # Full cleanup
make re     # Rebuild
```

---

## ⚠️ Key Challenges

- **Deadlock prevention** — careful fork-picking order
- **Data races** — every shared resource protected by a mutex
- **Death detection** — a monitor thread watching timestamps
- **Timing precision** — `usleep` isn't precise enough; custom sleep loops required

---

## 📋 Output Format

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

---

<div align="center">
<i>To eat or not to deadlock — that is the question.</i>
</div>
