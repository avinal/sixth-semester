/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * /media/avinal/ADVANCED/my_git/sixth-semester/computer_networks
 * @file 2node4router.cc
 * @author Avinal Kumar
 * @since April 20, 2021
 *
 * 6. Use NS-2/OMNET++ for showing the connection of 2 nodes and 4 router
 * such that the extremes nodes act as client and server.
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
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

#include "ns3/ipv4-global-routing-helper.h"
// Default Network Topology 10.1.5.0
// r2---------n1
// / 10.1.3.0
// no----------r0--------r1
// 10.1.1.0 10.1.2.0 \ 10.1.4.0
// r3
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("RouterScriptExample");

int main(int argc, char *argv[]) {
  bool verbose = true;
  if (verbose) {
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  }
  NodeContainer host, router, host1;
  host.Create(2);
  router.Create(4);

  NodeContainer subnet1;
  subnet1.Add(host.Get(0));
  subnet1.Add(router.Get(0));

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("50Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer subnet1Devices;
  subnet1Devices = pointToPoint.Install(subnet1);
  InternetStackHelper stack;
  stack.Install(router);
  stack.Install(host);

  Ipv4AddressHelper address1, address2, address3, address4, address5, address6;
  address1.SetBase("192.168.47.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet1Interfaces;
  subnet1Interfaces = address1.Assign(subnet1Devices);
  NodeContainer subnet2;

  subnet2.Add(router.Get(0));
  subnet2.Add(router.Get(1));
  NetDeviceContainer subnet2Devices;
  subnet2Devices = pointToPoint.Install(subnet2);

  address2.SetBase("192.168.48.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet2Interfaces;
  subnet2Interfaces = address2.Assign(subnet2Devices);
  NodeContainer subnet3;
  subnet3.Add(router.Get(1));
  subnet3.Add(router.Get(2));
  NetDeviceContainer subnet3Devices;
  subnet3Devices = pointToPoint.Install(subnet3);

  address3.SetBase("192.168.49.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet3Interfaces;
  subnet3Interfaces = address3.Assign(subnet3Devices);

  NodeContainer subnet4;
  subnet4.Add(router.Get(1));
  subnet4.Add(router.Get(3));
  NetDeviceContainer subnet4Devices;
  subnet4Devices = pointToPoint.Install(subnet4);

  address4.SetBase("192.168.50.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet4Interfaces;
  subnet4Interfaces = address4.Assign(subnet4Devices);
  NodeContainer subnet5;
  subnet5.Add(router.Get(2));
  subnet5.Add(host.Get(1));
  NetDeviceContainer subnet5Devices;
  subnet5Devices = pointToPoint.Install(subnet5);

  address5.SetBase("192.168.51.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet5Interfaces;
  subnet5Interfaces = address5.Assign(subnet5Devices);
  UdpEchoServerHelper echoServer(9);
  ApplicationContainer serverApps = echoServer.Install(subnet5.Get(1));
  serverApps.Start(Seconds(1.0));
  serverApps.Stop(Seconds(50.0));

  UdpEchoClientHelper echoClient(subnet5Interfaces.GetAddress(1), 9);
  echoClient.SetAttribute("MaxPackets", UintegerValue(3));
  echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
  echoClient.SetAttribute("PacketSize", UintegerValue(1024));
  ApplicationContainer clientApps = echoClient.Install(subnet1.Get(0));
  clientApps.Start(Seconds(1.0));
  clientApps.Stop(Seconds(50.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();
 pointToPoint.EnablePcapAll("second");

  Simulator::Run();
  Simulator::Destroy();

  return 0;
}