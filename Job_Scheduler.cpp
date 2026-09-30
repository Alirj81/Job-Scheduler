#include <iostream>
#include <string>
#include "Header.h"
#include <stdexcept>
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
        /*else { // this block is not needed since we are using member initializer list which already initializes the member variables
            this->id = id;
            this->description = description;
            this->priority = priority;
            this->duration = duration;
        }*/
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
    for (int i = 0; i < jobs.size(); ++i) {
        if (jobs[i].getId() == id) {
            return i; // Return the index of the job if found instead of the job ID. I totally misunderstood what i was doing here, maybe because i forgot the other methods that need to have the index of the job in the vector, so i will return the index instead of the job id, and then in the other methods i will use this index to access the job in the vector.
        }
    }
    return -1; // Job not found cuz the method is int and not bool
}

int JobManager::nextJob() {
    if (jobs.empty()) 
        throw std::runtime_error("No jobs available.");
    int highestPriorityIndex = 0;
    int highestpriority = jobs[0].getPriority();
    for (int i = 1; i < jobs.size(); ++i) {
        if (jobs[i].getPriority() > jobs[highestPriorityIndex].getPriority()) {
            highestpriority = jobs[i].getPriority();
            for(const auto& job : jobs){
                if(job.getPriority()==highestpriority){
                    return job.getId();
                }
            }
        }
        
    }
}
int JobManager :: totalDuration() const {
    int total = 0;
    for(const auto& job : jobs){
        total += job.getDuration();
    }
    return total;
}
// delete a job from the jobs vector
void JobManager :: cancelJob(int id) {
    int index = findJob(id);
    if (index == -1) {
        throw std::invalid_argument("Job not found.");
    }
    jobs.erase(jobs.begin() + index); // earase is a vector method. jobs.begin() + index is for accuracy for the pointer to where an element in the vector is.
}
