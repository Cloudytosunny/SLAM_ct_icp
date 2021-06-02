#ifndef CT_ICP_CT_ICP_H
#define CT_ICP_CT_ICP_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <list>

#define _USE_MATH_DEFINES

#include <fstream>
#include <vector>
#include <random>
#include <unordered_map>

#include "Eigen/Dense"

#include "types.hpp"


namespace ct_icp {

    // Subsample to keep one random point in every voxel of the current frame
    void sub_sample_frame(std::vector<Point3D> &frame, double size_voxel);

    // Samples Keypoints randomly in a voxel grid
    void grid_sampling(std::vector<Point3D> &frame, std::vector<Point3D> &keypoints, double size_voxel_subsampling);

    // Options for the CT_ICP
    struct CTICPOptions {

        double size_voxel_map = 1.0; //Max Voxel : -32767 to 32767 then 32km map for SIZE_VOXEL_MAP = 1m

        int num_iters_icp = 10;

        int min_number_neighbors = 20;

        int max_number_neighbors = 20;

        double max_dist_to_plane_ct_icp = 0.3;

        double norm_x_end_iteration_ct_icp = 0.001; // The threshold on the norm of the parameters vector

        bool debug_print = true; // Whether to output debug information to std::cout

        bool debug_interactive = true; // Whether to stop when an error has occured (calls std::system("PAUSE"))

    };

    // CT-ICP : Registers keypoints into the voxel_map
    // Note: CT_ICP will modify the last TrajectoryFrame of the trajectory vector
    int CT_ICP(const CTICPOptions &options,
               const VoxelHashMap &voxels_map, std::vector<Point3D> &keypoints,
               std::vector<TrajectoryFrame> &trajectory, int index_frame);


} // namespace CT_ICP


#endif //CT_ICP_CT_ICP_H