/**********************************************************************
 Copyright (c) 2020-2024, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/

#include "example.h"

int main(int argc, char *argv[])
{

    // Initialize via Serial (USB)
    UnitreeLidarReader *lreader = createUnitreeLidarReader();

    std::string port = "/dev/ttyACM0";
    uint32_t baudrate = 4000000;

    if (lreader->initializeSerial(port, baudrate))
    {
        printf("Unilidar initialization failed! Exit here!\n");
        exit(-1);
    }
    else
    {
        printf("Unilidar initialization succeed!\n");
    }

    sleep(1);

    // Parse IP arguments: set_ip_address <pc_ip> <lidar_ip>
    if (argc != 3)
    {
        printf("Usage: %s <pc_ip> <lidar_ip>\n", argv[0]);
        printf("Example: %s 192.168.50.15 192.168.50.51\n", argv[0]);
        exit(-1);
    }

    uint8_t pc_octets[4], lidar_octets[4];
    if (sscanf(argv[1], "%hhu.%hhu.%hhu.%hhu",
               &pc_octets[0], &pc_octets[1], &pc_octets[2], &pc_octets[3]) != 4 ||
        sscanf(argv[2], "%hhu.%hhu.%hhu.%hhu",
               &lidar_octets[0], &lidar_octets[1], &lidar_octets[2], &lidar_octets[3]) != 4)
    {
        printf("Invalid IP address format!\n");
        exit(-1);
    }

    printf("Setting PC IP: %s, Lidar IP: %s\n", argv[1], argv[2]);

    // Set lidar ip address
    LidarIpAddressConfig config;
    config.lidar_ip[0] = lidar_octets[0];
    config.lidar_ip[1] = lidar_octets[1];
    config.lidar_ip[2] = lidar_octets[2];
    config.lidar_ip[3] = lidar_octets[3];

    config.user_ip[0] = pc_octets[0];
    config.user_ip[1] = pc_octets[1];
    config.user_ip[2] = pc_octets[2];
    config.user_ip[3] = pc_octets[3];

    config.lidar_port = 6101;
    config.user_port = 6201;

    config.gateway[0] = 0;
    config.gateway[1] = 0;
    config.gateway[2] = 0;
    config.gateway[3] = 0;

    config.subnet_mask[0] = 255;
    config.subnet_mask[1] = 255;
    config.subnet_mask[2] = 255;
    config.subnet_mask[3] = 0;

    lreader->setLidarIpAddressConfig(config);
    std::cout << "Lidar IP is reset! Please reboot lidar!\n";
    sleep(1);
    

    return 0;
}