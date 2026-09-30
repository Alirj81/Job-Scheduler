#include <iostream>
#include <string>
#include "Header.h"
// Job block
// JOB class implementation
JOB::JOB(int id, std::string description, int priority, int duration)
    : id(id), description(description), priority(priority), duration(duration) {
        if (priority < 1 || priority > 5) {
            throw std::invalid_argument("Priority must be between 1 and 5.");
        }
        else if (duration <= 0) {
            throw std::invalid_argument("Duration must be a positive integer.");
        }
        else if (id < 0) {
            throw std::invalid_argument("ID must be a non-negative integer.");
        }
        else if (description.empty()) {
            throw std::invalid_argument("Description cannot be empty.");
        }
        else if (description.length() > 100) {
            throw std::invalid_argument("Description cannot exceed 100 characters.");
        }
        else {
            this->id = id;
            this->description = description;
            this->priority = priority;
            this->duration = duration;
        }
    }
// getter methods
std::string JOB::getDescription() const {
    return description;
}
int JOB::getPriority() const {
    return priority;
}
int JOB::getDuration() const {
    return duration;
}
int JOB::getId() const {
    return id;
}

// jobmanager block
// Job Manager class implementation
void JobManager::addJob(int id, std::string description, int priority, int duration) {
    if (findJob(id) != -1) {
        throw std::invalid_argument("Job ID must be unique.");
    }
    jobs.emplace_back(id, description, priority, duration);
}
int JobManager::findJob(int id) const {
    for (auto& job : jobs) {
        if (job.getId() == id) {
            return job.getId();
        }
    }
    return -1; // Job not found cuz the method is int and not bool
}
