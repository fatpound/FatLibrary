#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <cstddef>
#include <vector>

namespace fatx::opencv
{
    static auto FindLargestContour_(const std::vector<std::vector<cv::Point>>& contours, const double& maxArea) -> std::ptrdiff_t
    {
        std::ptrdiff_t largestIdx{ -1 };

        {
            double currentMaxArea{};

            for (std::size_t i{}, contoursSize{ contours.size() }; i < contoursSize; ++i)
            {
                if (const auto& area = cv::contourArea(contours[i]); area > maxArea and area > currentMaxArea)
                {
                    currentMaxArea = area;
                    largestIdx = i;
                }
            }
        }

        return largestIdx;
    }
}