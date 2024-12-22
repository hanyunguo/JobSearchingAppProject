#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMLManager.h"
#include "AddJobComponent.h"
#include "AddScheduleComponent.h"
#include "Task.h"
#include "PriorityTaskDecorator.h"

using ::testing::Return;

class MockXMLManager: public XMLManager {
public:
    MOCK_METHOD(bool, saveJobXML, (const Job &job), (override));
    MOCK_METHOD(bool, saveScheduleXML, (const Schedule &schedule), (override));

};

class MockTask : public Task {
public:
    MOCK_METHOD(QDateTime, getDeadline, (), (override));
    MOCK_METHOD(int, getPriority, (), (override));
    MOCK_METHOD(std::string, getTaskDescription, (), (override));
};

TEST(TaskDecoratorTest, TestDeadline) {
    MockTask mock;
    Task* target = new PriorityTaskDecorator(&mock, 2);
    QDate date(2024, 12, 1);
    QTime time(15, 0);  // 15:00:00 (3:00 PM)
    QDateTime dateTime(date, time);  // Combine date and time
    EXPECT_CALL(mock, getDeadline()).Times(1).WillOnce(Return(dateTime));
    EXPECT_EQ(target->getDeadline(), dateTime);
}

TEST(TaskDecoratorTest, TestPriority) {
    MockTask mock;
    Task* target = new PriorityTaskDecorator(&mock, 1);
    EXPECT_CALL(mock, getPriority()).Times(0);
    EXPECT_EQ(target->getPriority(), 1);
}

TEST(TaskDecoratorTest, TestTaskDescription){
    MockTask mock;
    Task* target = new TaskDecorator(&mock);
    EXPECT_CALL(mock, getTaskDescription()).Times(1).WillOnce(Return("Interview"));
    EXPECT_EQ(target->getTaskDescription(), "Interview");
}
// Test for successful job addition
TEST(AddJobComponentTest, TestsavaJobXML) {
    MockXMLManager mock;
    AddJobComponent testAddJobComponent;
    XMLManager* origin = XMLManager::getInstance();
    const Job testJob("Software Engineer", "Company X", "http://company.com/job123", "Job description");
    EXPECT_CALL(mock, saveJobXML(testJob)).Times(1).WillOnce(Return(true));
    XMLManager::setInstance(&mock);
    EXPECT_EQ(XMLManager::getInstance(), &mock);
    bool result = testAddJobComponent.addJob("Software Engineer", "Company X", "http://company.com/job123", "Job description");
    EXPECT_TRUE(result);
    XMLManager::setInstance(origin);
}

// Test for failed job addition (edge case)
TEST(JobListComponentTest, AddJobCallsXMLManagerFailure) {
    MockXMLManager mock;
    AddJobComponent testAddJobComponent;
    XMLManager* origin = XMLManager::getInstance();
    const Job testJob("Software Engineer", "Company X", "http://company.com/job123", "Job description");
    EXPECT_CALL(mock, saveJobXML(testJob)).Times(1).WillOnce(Return(false));
    XMLManager::setInstance(&mock);
    EXPECT_EQ(XMLManager::getInstance(), &mock);
    bool result = testAddJobComponent.addJob("Software Engineer", "Company X", "http://company.com/job123", "Job description");
    EXPECT_FALSE(result);
    XMLManager::setInstance(origin);
}

// Test for successful schedule addition
TEST(DailyPlannerComponentTest, AddScheduleCallsXMLManagerSuccess) {
    MockXMLManager mock;
    QDate date(2024, 12, 1);
    QTime time(14, 0);  // 14:00:00 (2:00 PM)
    QDateTime dateTime(date, time);  // Combine date and time

    // Convert QDateTime to time_t
    time_t timeStamp = dateTime.toSecsSinceEpoch();

    AddScheduleComponent testAddScheduleComponent(date, 14);
    XMLManager* origin = XMLManager::getInstance();
    const Schedule testSchedule(timeStamp, "CS 3307", "Final Project", true);
    EXPECT_CALL(mock, saveScheduleXML(testSchedule)).Times(1).WillOnce(Return(true));
    XMLManager::setInstance(&mock);
    EXPECT_EQ(XMLManager::getInstance(), &mock);
    bool result = testAddScheduleComponent.addSchedule(date, 14, "CS 3307", "Final Project", true);
    EXPECT_TRUE(result);
    XMLManager::setInstance(origin);
}

// Test for failed schedule addition (edge case)
TEST(DailyPlannerComponentTest, AddScheduleCallsXMLManagerFailure) {
    MockXMLManager mock;
    QDate date(2024, 12, 1);
    QTime time(14, 0);  // 14:00:00 (2:00 PM)
    QDateTime dateTime(date, time);  // Combine date and time

    // Convert QDateTime to time_t
    time_t timeStamp = dateTime.toSecsSinceEpoch();

    AddScheduleComponent testAddScheduleComponent(date, 14);
    XMLManager* origin = XMLManager::getInstance();
    const Schedule testSchedule(timeStamp, "CS 3307", "Final Project", true);
    EXPECT_CALL(mock, saveScheduleXML(testSchedule)).Times(1).WillOnce(Return(false));
    XMLManager::setInstance(&mock);
    EXPECT_EQ(XMLManager::getInstance(), &mock);
    bool result = testAddScheduleComponent.addSchedule(date, 14, "CS 3307", "Final Project", true);
    EXPECT_FALSE(result);
    XMLManager::setInstance(origin);
}
