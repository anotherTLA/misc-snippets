#!/usr/bin/env python

"""
An example using Domains to create a two-domain Mininet network, each with its
own controller.
"""

from domains import Domain
from mininet.net import Mininet
from mininet.cli import CLI 
from mininet.log import setLogLevel, info

class TestDomain(Domain):
    """
    A tiny domain of three nodes connected in a triangle
    """
    def build(self):
        sw1 = 'sw%s1' % self.getId()
        sw2 = 'sw%s2' % self.getId()
        sw3 = 'sw%s3' % self.getId()

        self.addSwitch(sw1)
        self.addSwitch(sw2)
        self.addSwitch(sw3)

        self.addLink(sw1, sw2)
        self.addLink(sw2, sw3)
        self.addLink(sw3, sw1)


if __name__ == '__main__':
    setLogLevel('info')

    # make test domains with unique IDs '1' and '2'
    domain1 = TestDomain(1)
    domain2 = TestDomain(2)
    # add controllers to them, and build
    domain1.addController('c1')
    domain1.addController('c2')
    domain1.build()
    domain2.build()

    # add prepared domains to the network, and initialise
    net = Mininet()
    domain1.injectInto(net)
    domain2.injectInto(net)
    net.build()

    # connect domains 1 and 2 - currently needs to be done after network is built    
    Domain.interConnect(domain1.getSwitches('sw11'), domain2.getSwitches('sw21'), net)

    domain1.start()
    domain2.start()

    # add a CLI to interact with the network
    CLI(net)
    net.stop()
