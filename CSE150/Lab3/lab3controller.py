# Lab 3 Skeleton
#
# Based on of_tutorial by James McCauley

from pox.core import core
import pox.openflow.libopenflow_01 as of
import pox.lib.packet as pkt
import time

log = core.getLogger()
_flood_delay = 0

class Firewall (object):
  """
  A Firewall object is created for each switch that connects.
  A Connection object for that switch is passed to the __init__ function.
  """
  def __init__ (self, connection):
    # Keep track of the connection to the switch so that we can
    # send it messages!
    self.connection = connection

    # This binds our PacketIn event listener
    connection.addListeners(self)
    self.hold_down_expired = _flood_delay == 0

  def do_firewall (self, packet, packet_in, event):
    # The code in here will be executed for every packet.

    # Step 1: Parse the packets
    # See http://intronetworks.cs.luc.edu/auxiliary_files/mininet/poxwiki.pdf
    # Pages 21-24

    # Step 2: Define entries and install them into the table
    # See http://intronetworks.cs.luc.edu/auxiliary_files/mininet/poxwiki.pdf
    # Pages 32-39

    def flood(message = None):
      # code for flood
      # See flood() in l2_learning.py
      """ Floods the packet """
      msg = of.ofp_packet_out()
      msg.match = of.ofp_match.from_packet(packet)
      msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
      msg.data = event.ofp
      msg.in_port = event.port
      self.connection.send(msg)
      
    def drop(duration = None):
      # code for drop
      # See drop() in l2_learning.py
      """
      Drops this packet and optionally installs a flow to continue
      dropping similar ones for a while
      """
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.idle_timeout = 300
      msg.hard_timeout = 300
      msg.buffer_id = event.ofp.buffer_id
      self.connection.send(msg)
      
    ip = packet.find('ipv4')
    tcp_found = packet.find('tcp')
    arp_found = packet.find('arp')

    # Condition 1
    if(tcp_found is not None) and (ip is not None):
      print("tcp and ipv4")
      flood()

    # Condition 2 
    elif arp_found is not None:
      print("arp")
      flood()

    # Condition 3
    else:
      print("dropping")
      drop()

    # print "Example Code."


  def _handle_PacketIn (self, event):
    """
    Handles packet in messages from the switch.
    """

    packet = event.parsed # This is the parsed packet data.
    if not packet.parsed:
      log.warning("Ignoring incomplete packet")
      return

    packet_in = event.ofp # The actual ofp_packet_in message.
    self.do_firewall(packet, packet_in, event)

def launch ():
  """
  Starts the component
  """
  def start_switch (event):
    log.debug("Controlling %s" % (event.connection,))
    Firewall(event.connection)
  core.openflow.addListenerByName("ConnectionUp", start_switch)
