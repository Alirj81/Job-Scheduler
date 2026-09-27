#pragma once
#include <vector>
#include <string>

class JOB{
public:
    
    JOB(int id, std::string description, int priority, int duration);
    
    std::string getDescription() const;
    int getPriority() const;
    int getDuration() const;
    int getId() const;
    

private:
    int id; 
    std::string description;
    int priority;
    int duration;
};
class JobManager {
    public:
    void addJob(int id, std::string description, int priority, int duration);
    int findJob(int id) const;
    
    
    void cancelJob(int id);
    int nextJob() const;
    int totalDuration() const;
    int jobpriority(int id) const;
    void cancelJob(int id);
    private:
    std::vector<JOB> jobs;

};
