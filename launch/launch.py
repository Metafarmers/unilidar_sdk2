import os
import subprocess

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():

    local_ip_arg = DeclareLaunchArgument('local_ip', default_value='192.168.50.4')
    lidar_ip_arg = DeclareLaunchArgument('lidar_ip', default_value='192.168.50.51')

    # Run unitree lidar
    node1 = Node(
        package='unitree_lidar_ros2',
        executable='unitree_lidar_ros2_node',
        name='unitree_lidar_ros2_node',
        output='screen',
        parameters= [

                {'initialize_type': 2},
                {'work_mode': 0},
                {'use_system_timestamp': True},
                {'range_min': 0.0},
                {'range_max': 100.0},
                {'cloud_scan_num': 18},

                {'lidar_port': 6101},
                {'lidar_ip': LaunchConfiguration('lidar_ip')},
                {'local_port': 6201},
                {'local_ip': LaunchConfiguration('local_ip')},

                {'cloud_frame': "front_3d_lidar_link"},
                {'cloud_topic': "front_3d/points"},
                {'imu_frame': "front_3d_lidar_imu_link"},
                {'imu_topic': "front_3d/imu"},
                ]
    )

    # Run Rviz
    #package_path = subprocess.check_output(['ros2', 'pkg', 'prefix', 'unitree_lidar_ros2']).decode('utf-8').rstrip()
    #rviz_config_file = os.path.join(package_path, 'share', 'unitree_lidar_ros2', 'view.rviz')
    #print("rviz_config_file = " + rviz_config_file)
    #rviz_node = Node(
    #    package='rviz2',
    #    executable='rviz2',
    #    name='rviz2',
    #    arguments=['-d', rviz_config_file],
    #    output='log'
    #)
    return LaunchDescription([local_ip_arg, lidar_ip_arg, node1])
