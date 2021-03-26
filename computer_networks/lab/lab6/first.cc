/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * /mnt/z/my_git/sixth-semester/computer_networks/simulation/scratch/lab/first.cc
 * @file first.cc
 * @author Avinal Kumar
 * @since March 26, 2021
 *
 * Point to Point UDP Network Simulation
 * Data Rate:             200mbps
 * Transmission Delay:    5ms
 * Base Address:          172.16.1.0
 * UDP Server Start Time: 2 sec
 * UDP Server Stop Time:  25 sec
 * UDP Packet Interval:   1.5 sec
 * Number of packets:     10
 * UDP Packet Size:       2048 bytes
 * UDP Client Start Time: 2 sec
 * UDP Client Stop Time:  25 sec
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include <iostream>

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1
//    point-to-point
//

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FirstScriptExample");

int main(int argc, char *argv[]) {
  std::cout << "* Point to Point UDP Network Simulation" << std::endl
            << "* Data Rate:             200mbps" << std::endl
            << "* Transmission Delay:    5ms" << std::endl
            << "* Base Address:          172.16.1.0" << std::endl
            << "* UDP Server Start Time: 2 sec" << std::endl
            << "* UDP Server Stop Time:  25 sec" << std::endl
            << "* UDP Packet Interval:   1.5 sec" << std::endl
            << "* Number of packets:     10" << std::endl
            << "* UDP Packet Size:       2048 bytes" << std::endl
            << "* UDP Client Start Time: 2 sec" << std::endl
            << "* UDP Client Stop Time:  25 sec\n"
            << std::endl
            << "Default Network Topology" << std::endl
            << "      10.1.1.0" << std::endl
            << "n0 -------------- n1" << std::endl
            << "   point-to-point\n"
            << std::endl;

  CommandLine cmd(__FILE__);
  cmd.Parse(argc, argv);

  Time::SetResolution(Time::NS);
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create(2);

  PointToPointHelper pointToPoint;
  // 1. Set the Data rate of the point to point channel to 200Mbps
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("200Mbps"));
  // 2. Set the Transmission Delay of the channel to 5ms
  pointToPoint.SetChannelAttribute("Delay", StringValue("5ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install(nodes);

  InternetStackHelper stack;
  stack.Install(nodes);

  Ipv4AddressHelper address;
  // 3. Change the base address of the point to point network to 172.16.1.0
  address.SetBase("172.16.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign(devices);

  UdpEchoServerHelper echoServer(9);

  ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
  // 4. Start the UDP server at 2 seconds into the start of the simulation
  serverApps.Start(Seconds(2.0));
  // 5. Stop the UDP server after 25 seconds into the simulation
  serverApps.Stop(Seconds(25.0));

  UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
  // 7. Set the number of packets transmitted from client to server equal to 10
  echoClient.SetAttribute("MaxPackets", UintegerValue(10));
  // 6. Set the UDP packets interval from client to server as 1.5 sec.
  echoClient.SetAttribute("Interval", TimeValue(Seconds(1.5)));
  // 8. Set the UDP packet size sent from client to server as 2048 bytes.
  echoClient.SetAttribute("PacketSize", UintegerValue(2048));

  ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
  // 9. Start the UDP client at 2 seconds into the start of the simulation
  clientApps.Start(Seconds(2.0));
  // 10. Stop the UDP client after 25 seconds into the simulation
  clientApps.Stop(Seconds(25.0));

  Simulator::Run();
  Simulator::Destroy();
  return 0;
}
