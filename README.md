# Emergency Job Scheduler — C++

A small C++ learning project for managing pending jobs by priority. I built it to practise object-oriented design, encapsulation, validation, and STL algorithms while improving how I reason about code.

The scheduler supports adding, finding, and cancelling jobs, selecting the most urgent job, calculating total estimated duration, and displaying jobs in priority order.

## Features

- Job creation with input validation and unique IDs.
- ID-based search and cancellation.
- Highest-priority job selection, with priority **5** being the most urgent.
- First-added selection among equally urgent jobs.
- Display of all jobs tied at the highest priority.
- Total duration calculation for pending jobs.
- Stable sorting by descending priority using `std::stable_sort`.
- A private `std::vector<JOB>` managed through public methods.

## Design

The project separates two responsibilities:

| Class | Responsibility |
|---|---|
| `JOB` | Stores one job's ID, description, priority, and duration; exposes getters. |
| `JobManager` | Owns the collection and handles scheduling operations. |

The manager **contains** jobs rather than inheriting from a job. Both the job fields and the manager's vector are private. The manager reads job data through public getters.

The implementation uses `std::string`, const methods, and const references in loops and comparisons. It does not use raw `new` or `delete`.

## Operations

These names reflect the current implementation:

| Method | Behavior |
|---|---|
| `addJob(id, description, priority, duration)` | Rejects duplicate IDs and constructs a validated job. |
| `findJob(id) const` | Returns the current zero-based vector index, or `-1` if absent. |
| `cancelJob(id)` | Removes the matching job; throws if it is absent. |
| `nextJob() const` | Prints IDs of all highest-priority jobs and returns one selected job ID. Throws when empty. |
| `totalDuration() const` | Returns the sum of all pending job durations in seconds. |
| `jobsbyPriority()` | Sorts the internal vector and prints each job's details. |

`nextJob()` leaves the selected job pending. Repeated calls select the same job unless the collection changes. Equal priorities are allowed; IDs must be unique.

`findJob()` returns a location, not an identity: sorting or removing jobs can change that index. `jobsbyPriority()` modifies the collection's order, so it is not const. Stable sorting preserves the relative order of jobs sharing a priority.

## Validation

The constructor rejects:

- Priorities outside **1–5**.
- Durations at or below zero.
- Negative IDs.
- Empty descriptions.
- Descriptions longer than 100 characters.

Invalid inputs and duplicate IDs produce `std::invalid_argument`. An empty collection in `nextJob()` produces `std::runtime_error`.

## Build and use

Use a C++ compiler with C++11 support or newer. The example below assumes a `main.cpp` entry point and a `JobManager.cpp` implementation file; substitute your actual filenames.

```bash
g++ -std=c++11 -Wall -Wextra -Wpedantic main.cpp JobManager.cpp -o scheduler
./scheduler
```

The scheduler is a class-based component. A `main()` function is needed to create a manager and call its methods; no interactive command-line interface is documented here.

Example calls from a program:

```cpp
JobManager scheduler;
scheduler.addJob(42, "Process emergency request", 5, 30);
scheduler.addJob(90, "Generate report", 3, 60);
scheduler.addJob(12, "Handle urgent notification", 5, 20);

scheduler.jobsbyPriority();
int selectedId = scheduler.nextJob();
int pendingSeconds = scheduler.totalDuration();
scheduler.cancelJob(selectedId);
```

With these jobs, the total duration is 110 seconds. Jobs 42 and 12 share the highest priority, and job 42 is selected first. These are expected outcomes illustrating the API, rather than a recorded test run.

## What I learned

My first design mixed the data of one job with operations on the entire collection. Separating `JOB` from `JobManager` helped me understand composition and ownership.

Another important correction was distinguishing a job ID from its vector index. That changed how I thought about method return values and how cancellation uses search results.

While implementing `nextJob()`, I initially returned before examining every job. Tracing small examples helped me see why the search must finish before returning the result. Working through duplicate priorities also clarified the difference between selecting one job and displaying all equally urgent jobs.

Sorting introduced me to lambdas and comparator functions. I learned how to express an ordering rule using const references, and why `std::stable_sort` fits the decision to preserve order among tied jobs. Switching from `printf` to `std::cout` also made string output clearer.

I used ChatGPT for guided feedback and explanations while writing and revising the implementation myself.

## Project journal

The accompanying Jupyter notebook records the development journey, design decisions, mistakes, corrections, and personal reflections. It uses Markdown cells with C++ examples and can be opened in JupyterLab without a C++ kernel.

Include `emergency_job_scheduler_learning_journal.ipynb` alongside this README to keep the reasoning with the code.

## Scope

This is an educational scheduler that stores pending jobs in memory. It selects and lists jobs; it does not execute them or persist them to disk. The documented implementation uses one STL algorithm, `std::stable_sort`; it does not include the separate business-value dynamic-programming challenge from the original exercise.

## Author

**Alireza Jamshidian Tehrani (Ali)** — B.Sc. Computer Science student at the University of Wuppertal.
