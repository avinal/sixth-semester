/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * /media/avinal/ADVANCED/my_git/sixth-semester/computer_networks/lab/lab7/second.cc
 * @file second.cc
 * @author Avinal Kumar
 * @since April 02, 2021
 *
 * Point to Point Network with 7 CSMA Stations
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
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include <iostream>

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1   n2   n3   n4   n5   n6   n7
//    point-to-point  |    |    |    |    |    |    |
//                    ===============================
//                              LAN 10.1.2.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SecondScriptExample");

int main(int argc, char *argv[]) {
  bool verbose = true;
  // 1. Increase the number of stations in the CSMA LAN network to 7 nodes.
  uint32_t nCsma = 6;

  CommandLine cmd;
  cmd.AddValue("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
  cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse(argc, argv);

  if (verbose) {
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  }

  nCsma = nCsma == 0 ? 1 : nCsma;
  std::cout << "P2P Bus Topology Network with 7 CSMA stations\n"
            << std::endl
            << "       10.1.1.0" << std::endl
            << " n0 -------------- n1   n2   n3   n4   n5   n6   n7"
            << std::endl
            << "    point-to-point  |    |    |    |    |    |    |"
            << std::endl
            << "                    ==============================="
            << std::endl
            << "                              LAN 10.1.2.0\n"
            << std::endl;
  NodeContainer p2pNodes;
  p2pNodes.Create(2);

  NodeContainer csmaNodes;
  csmaNodes.Add(p2pNodes.Get(1));
  csmaNodes.Create(nCsma);

  PointToPointHelper pointToPoint;
  // 2. Set the datarate of the point to point link to 20 Mbps with a delay of
  // 5ms.
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("20Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("5ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install(p2pNodes);

  CsmaHelper csma;
  // 3. Set the datarate of the CSMA network to 300 Mbps with a delay of 10,000
  // nanoseconds
  csma.SetChannelAttribute("DataRate", StringValue("300Mbps"));
  csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(10000)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install(csmaNodes);

  InternetStackHelper stack;
  stack.Install(p2pNodes.Get(0));
  stack.Install(csmaNodes);

  Ipv4AddressHelper address;
  address.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign(p2pDevices);

  address.SetBase("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign(csmaDevices);

  // 4. Make the 4th node in the CSMA network as the UDP Echoserver listening at
  // port 15.
  UdpEchoServerHelper echoServer(15);

  ApplicationContainer serverApps = echoServer.Install(csmaNodes.Get(4));
  // 5. Start the UDP server at 2.0 seconds and stop it at 12 seconds.
  serverApps.Start(Seconds(2.0));
  serverApps.Stop(Seconds(15.0));

  UdpEchoClientHelper echoClient(csmaInterfaces.GetAddress(4), 15);
  // 6. Set the Max number of packets, Packet interval time and packet size of
  // the UDP client running at the leftmost node of the point to point link to
  // 6, 1.5 seconds and 2048 bytes respectively.
  echoClient.SetAttribute("MaxPackets", UintegerValue(6));
  echoClient.SetAttribute("Interval", TimeValue(Seconds(1.5)));
  echoClient.SetAttribute("PacketSize", UintegerValue(2048));

  ApplicationContainer clientApps = echoClient.Install(p2pNodes.Get(0));
  // 8. Start the UDP client at 3.0 seconds and stop it at 14 seconds.
  clientApps.Start(Seconds(3.0));
  clientApps.Stop(Seconds(14.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  pointToPoint.EnablePcapAll("second");
  // 7. Set the 3rd device on the CSMA network to capture the packets in a
  // promiscuous mode.
  csma.EnablePcap("second", csmaDevices.Get(3), true);

  Simulator::Run();
  Simulator::Destroy();
  return 0;
}
