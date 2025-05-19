#pragma once

#include <FatMacros.hpp>

#pragma warning (push)
#pragma warning (disable : FAT_EXTERNAL_WARNINGS)
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#pragma warning (pop)

#include <cstddef>
#include <vector>

namespace fatx::opencv
{
    static auto FindLargestContour(const std::vector<std::vector<cv::Point>>& contours, const double& maxArea) -> std::ptrdiff_t
    {
        std::ptrdiff_t largestIdx{ -1 };

        {
            double currentMaxArea{};

            for (std::size_t i{}; i < contours.size(); ++i)
            {
                if (const auto& area = cv::contourArea(contours[i]); area > maxArea and area > currentMaxArea)
                {
                    currentMaxArea = area;
                    largestIdx     = static_cast<decltype(largestIdx)>(i);
                }
            }
        }

        return largestIdx;
    }
}