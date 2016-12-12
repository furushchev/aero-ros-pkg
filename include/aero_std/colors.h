#ifndef _AERO_STD_COLORS_
#define _AERO_STD_COLORS_

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <array>

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace aero
{
  namespace colors
  {

    //////////////////////////////////////////////////
    inline std::array<float, 3> rgb2lab(cv::Vec3b _color) // bgr
    {
      std::array<float, 3> adapt = {0.950467, 1.0, 1.088969};

      std::function<float(float)> g = [=](float _v) {
        _v = _v * 0.003922;
        if (_v <= 0.04045) return _v * 0.07739938;
        else return std::pow((_v + 0.055) / 1.055, 2.4);
      };

      std::array<float, 3> rgb = {g(_color[2]), g(_color[1]), g(_color[0])};

      std::array<float, 3> xyz = {
        0.412424 * rgb[0] + 0.357579 * rgb[1] + 0.180464 * rgb[2],
        0.212656 * rgb[0] + 0.715158 * rgb[1] + 0.0721856 * rgb[2],
        0.0193324 * rgb[0] + 0.119193 * rgb[1] + 0.950444 * rgb[2]
      };

      std::function<float(float)> f = [=](float _v) {
        if (_v > 0.008856) return std::pow(_v, 0.333333);
        else return _v * 7.787 + 0.137931;
      };

      std::array<float, 3> lab = {
        116 * f(xyz[1] / adapt[1]) - 16,
        500 * (f(xyz[0] / adapt[0]) - f(xyz[1] / adapt[1])),
        200 * (f(xyz[1] / adapt[1]) - f(xyz[2] / adapt[2]))
      };

      return lab;
    };

    //////////////////////////////////////////////////
    inline float distance(std::array<float, 3> _color1, std::array<float, 3> _color2)
    {
      // input must be in lab space

      float L = (_color1[0] + _color2[0]) * 0.5;
      float dL = _color1[0] - _color2[0];

      float C7 = std::pow(
          (sqrt(_color1[1] * _color1[1] + _color1[2] * _color1[2]) +
           sqrt(_color2[1] * _color2[1] + _color2[2] * _color2[2])) * 0.5, 7);
      float sqC = sqrt(C7 / (C7 + 6103515625));
      float a1 = _color1[1] * (1.0 + 0.5 * (1 - sqC));
      float a2 = _color2[1] * (1.0 + 0.5 * (1 - sqC));
      float c1 = sqrt(a1 * a1 + _color1[2] * _color1[2]);
      float c2 = sqrt(a2 * a2 + _color2[2] * _color2[2]);
      float C = (c2 + c1) * 0.5;
      float dC = c2 - c1;

      if (fabs(a1) < 0.000001) a1 = 0.000001;
      if (fabs(a2) < 0.000001) a2 = 0.000001;
      float h1 = atan2(_color1[2], a1);
      if (h1 < 0) h1 += 2 * M_PI;
      float h2 = atan2(_color2[2], a2);
      if (h2 < 0) h2 += 2 * M_PI;
      float H = fabs(h2 - h1);
      if (H <= M_PI) {
        H = (h1 + h2) * 0.5;
      } else {
        H = h1 + h2;
        if (H < 2 * M_PI) H = H * 0.5 + M_PI;
        else H = H * 0.5 - M_PI;
      }
      float dh = h2 - h1;
      if (dh < -M_PI) dh += 2 * M_PI;
      else if (dh > M_PI) dh -= 2 * M_PI;
      float dH = 2 * sqrt(c1 * c2) * sin(dh * 0.5);

      float Sl = 1 + 0.015 * std::pow(L - 50, 2) / sqrt(20 + std::pow(L - 50, 2));
      float Sc = 1 + 0.045 * C;
      float Sh = 1 + 0.015 * C *
        (1 - 0.17 * cos(H - 0.5235988) + 0.24 * cos(2 * H) +
         0.32 * cos(3 * H + 0.1047198) - 0.20 * cos(4 * H - 1.0995574));
      float Rt = -2 * sqC *
        sin(1.0471976 * std::exp(-std::pow((H - 4.7996554) / 0.4363323, 2)));

      return sqrt(std::pow(dL / Sl, 2) + std::pow(dC / Sc, 2) +
                  std::pow(dH / Sh, 2) + Rt * dC * dH / (Sc * Sh));
    };

    //////////////////////////////////////////////////
    void MedianCut(std::vector<cv::Vec3b> _img, int _bucket_idx, int _layer,
                   std::vector<cv::Vec3b> &_palettes)
    {
      if (_layer >= log2(_palettes.size())) {
        std::array<int, 3> average_rgb = {0, 0, 0};
        for (unsigned int i = 0; i < _img.size(); ++i) {
          average_rgb[0] += _img[i][0];
          average_rgb[1] += _img[i][1];
          average_rgb[2] += _img[i][2];
        }
        average_rgb[0] /= _img.size();
        average_rgb[1] /= _img.size();
        average_rgb[2] /= _img.size();
        _palettes[_bucket_idx] =
          cv::Vec3b(average_rgb[0], average_rgb[1], average_rgb[2]);

        return;
      }

      cv::Vec3b max(0, 0, 0);
      cv::Vec3b min(255, 255, 255);

      for (auto it = _img.begin(); it != _img.end(); ++it) {
        if ((*it)[0] > max[0]) max[0] = (*it)[0];
        if ((*it)[0] < min[0]) min[0] = (*it)[0];
        if ((*it)[1] > max[1]) max[1] = (*it)[1];
        if ((*it)[1] < min[1]) min[1] = (*it)[1];
        if ((*it)[2] > max[2]) max[2] = (*it)[2];
        if ((*it)[2] < min[2]) min[2] = (*it)[2];
      }

      cv::Vec3b range = {max[0] - min[0], max[1] - min[1], max[2] - min[2]};
      std::function<bool(cv::Vec3b, cv::Vec3b)> compare;

      if (range[0] > range[1]) {
        if (range[0] > range[2])
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[0] > b[0];};
        else
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[2] > b[2];};
      } else {
        if (range[1] > range[2])
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[1] > b[1];};
        else
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[2] > b[2];};
      }

      std::sort(_img.begin(), _img.end(), compare);
      int mid = _img.size() * 0.5;

      std::vector<cv::Vec3b> bucket_one(_img.begin(), _img.begin() + mid);
      std::vector<cv::Vec3b> bucket_two(_img.begin() + mid, _img.end());

      ++_layer;

      MedianCut(bucket_one, _bucket_idx, _layer, _palettes);
      MedianCut(bucket_two, _bucket_idx + _palettes.size()/(2*_layer), _layer,
                _palettes);
    };

    //////////////////////////////////////////////////
    void MedianCut(cv::Mat _img, int _bucket_idx, int _layer,
                   std::vector<cv::Vec3b> &_palettes)
    {
      cv::Vec3b max(0, 0, 0);
      cv::Vec3b min(255, 255, 255);

      for (auto it = _img.begin<cv::Vec3b>(); it != _img.end<cv::Vec3b>(); ++it) {
        if ((*it)[0] > max[0]) max[0] = (*it)[0];
        if ((*it)[0] < min[0]) min[0] = (*it)[0];
        if ((*it)[1] > max[1]) max[1] = (*it)[1];
        if ((*it)[1] < min[1]) min[1] = (*it)[1];
        if ((*it)[2] > max[2]) max[2] = (*it)[2];
        if ((*it)[2] < min[2]) min[2] = (*it)[2];
      }

      cv::Vec3b range = {max[0] - min[0], max[1] - min[1], max[2] - min[2]};
      std::function<bool(cv::Vec3b, cv::Vec3b)> compare;

      if (range[0] > range[1]) {
        if (range[0] > range[2])
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[0] > b[0];};
        else
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[2] > b[2];};
      } else {
        if (range[1] > range[2])
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[1] > b[1];};
        else
          compare = [=](cv::Vec3b a, cv::Vec3b b){return a[2] > b[2];};
      }

      std::sort(_img.begin<cv::Vec3b>(), _img.end<cv::Vec3b>(), compare);
      int mid = _img.cols * _img.rows * 0.5;

      std::vector<cv::Vec3b> bucket_one
        (_img.begin<cv::Vec3b>(), _img.begin<cv::Vec3b>() + mid);
      std::vector<cv::Vec3b> bucket_two
        (_img.begin<cv::Vec3b>() + mid, _img.end<cv::Vec3b>());

      if (_palettes.size() == 1) {
        std::array<int, 3> average_rgb = {0, 0, 0};
        for (unsigned int i = 0; i < bucket_one.size(); ++i) {
          average_rgb[0] += bucket_one[i][0];
          average_rgb[1] += bucket_one[i][1];
          average_rgb[2] += bucket_one[i][2];
        }
        average_rgb[0] /= bucket_one.size();
        average_rgb[1] /= bucket_one.size();
        average_rgb[2] /= bucket_one.size();
        _palettes[_bucket_idx] =
          cv::Vec3b(average_rgb[0], average_rgb[1], average_rgb[2]);

        return;
      }

      ++_layer;

      MedianCut(bucket_one, _bucket_idx, _layer, _palettes);
      MedianCut(bucket_two, _bucket_idx + _palettes.size()/(2*_layer), _layer,
                _palettes);
    };

  }
}

#endif
