#include "utils/DateUtils.h"
#include "utils/Constants.h"
#include <gtest/gtest.h>

TEST(GetLastDayOfMonthTest, January) {
    EXPECT_EQ(utils::getLastDayOfMonth(1, 2024), 31);
}

TEST(GetLastDayOfMonthTest, FebruaryLeapYear) {
    EXPECT_EQ(utils::getLastDayOfMonth(2, 2024), 29);
}

TEST(GetLastDayOfMonthTest, FebruaryNonLeapYear) {
    EXPECT_EQ(utils::getLastDayOfMonth(2, 2023), 28);
}

TEST(GetLastDayOfMonthTest, FebruaryCenturyLeap) {
    EXPECT_EQ(utils::getLastDayOfMonth(2, 2000), 29);
}

TEST(GetLastDayOfMonthTest, FebruaryCenturyNonLeap) {
    EXPECT_EQ(utils::getLastDayOfMonth(2, 1900), 28);
}

TEST(GetLastDayOfMonthTest, April) {
    EXPECT_EQ(utils::getLastDayOfMonth(4, 2024), 30);
}

TEST(GetLastDayOfMonthTest, June) {
    EXPECT_EQ(utils::getLastDayOfMonth(6, 2024), 30);
}

TEST(GetLastDayOfMonthTest, December) {
    EXPECT_EQ(utils::getLastDayOfMonth(12, 2024), 31);
}

TEST(GetLastDayOfMonthTest, InvalidMonthZero) {
    EXPECT_EQ(utils::getLastDayOfMonth(0, 2024), 0);
}

TEST(GetLastDayOfMonthTest, InvalidMonthThirteen) {
    EXPECT_EQ(utils::getLastDayOfMonth(13, 2024), 0);
}

TEST(GetMonthDateRangeTest, JanuaryRange) {
    auto [start, end] = utils::getMonthDateRange(1, 2024);
    EXPECT_EQ(start, "2024-01-01");
    EXPECT_EQ(end, "2024-01-31");
}

TEST(GetMonthDateRangeTest, FebruaryLeapRange) {
    auto [start, end] = utils::getMonthDateRange(2, 2024);
    EXPECT_EQ(start, "2024-02-01");
    EXPECT_EQ(end, "2024-02-29");
}

TEST(GetMonthDateRangeTest, FebruaryNonLeapRange) {
    auto [start, end] = utils::getMonthDateRange(2, 2023);
    EXPECT_EQ(start, "2023-02-01");
    EXPECT_EQ(end, "2023-02-28");
}

TEST(GetMonthDateRangeTest, NovemberRange) {
    auto [start, end] = utils::getMonthDateRange(11, 2025);
    EXPECT_EQ(start, "2025-11-01");
    EXPECT_EQ(end, "2025-11-30");
}

TEST(GetMonthDateRangeTest, DecemberRange) {
    auto [start, end] = utils::getMonthDateRange(12, 2026);
    EXPECT_EQ(start, "2026-12-01");
    EXPECT_EQ(end, "2026-12-31");
}

TEST(ConstantsTest, BudgetThresholds) {
    EXPECT_DOUBLE_EQ(constants::budget::WARNING_THRESHOLD, 80.0);
    EXPECT_DOUBLE_EQ(constants::budget::EXCEEDED_THRESHOLD, 100.0);
}

TEST(ConstantsTest, ValidationBounds) {
    EXPECT_EQ(constants::validation::MIN_MONTH, 1);
    EXPECT_EQ(constants::validation::MAX_MONTH, 12);
    EXPECT_EQ(constants::validation::MIN_YEAR, 2000);
    EXPECT_DOUBLE_EQ(constants::validation::PERCENTAGE_MULTIPLIER, 100.0);
}
