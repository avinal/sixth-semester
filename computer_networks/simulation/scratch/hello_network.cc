/**
 * /mnt/z/my_git/sixth-semester/computer_networks/simulation/practice/hello_network.cc
 * @author Avinal Kumar
 * @since February 02, 2021
 *
 * Network Simulation Hello World
 */

#include "ns3/core-module.h"

NS_LOG_COMPONENT_DEFINE("HelloNetwork");

int main(int argc, char const *argv[])
{
    NS_LOG_UNCOND("Hello Network");

    ns3::Simulator::Run();
    ns3::Simulator::Destroy();
}
