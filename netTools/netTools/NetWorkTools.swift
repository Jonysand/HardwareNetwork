//
//  NetWorkTools.swift
//  netTools
//
//  Created by Yongkun Li on 2/13/20.
//  Copyright © 2020 Yongkun Li. All rights reserved.
//

import Foundation
import Network

class NetWorkTools {
    var connection: NWConnection?
    var status: String
    
    init() {
        self.status = "Not begun"
    }
    
    
    func startTCP(host: String, port: Int){
        let connection = NWConnection(host: NWEndpoint.Host.init(host), port: NWEndpoint.Port.init(rawValue: UInt16(port))!, using: .tcp)
        connection.stateUpdateHandler = self.stateDidChange(to:)
        self.setupReceive(on: connection)
        connection.start(queue: .main)
        self.connection = connection
        self.status = "Connected"
    }
    
    func stateDidChange(to state: NWConnection.State) {
        switch state {
        case .setup:
            self.status = "setup"
        case .waiting:
            self.status = "Waiting"
        case .preparing:
            self.status = "preparing"
        case .ready:
            self.status = "Connected"
        case .failed:
            self.status = "Connection Failed"
        case .cancelled:
            self.status = "cancelled"
        @unknown default:
            return
        }
    }
    
    func setupReceive(on connection: NWConnection) {
        connection.receive(minimumIncompleteLength: 1, maximumLength: 65536) { (data, contentContext, isComplete, error) in
            if let data = data, !data.isEmpty {
                // … process the data …
                self.status = "did receive \(data.count) bytes"
            }
            if isComplete {
                // … handle end of stream …
                self.status = "Receiving completed"
            } else if error != nil {
                // … handle error …
                self.status = "Receiving error"
            } else {
                self.setupReceive(on: connection)
            }
        }
    }

    func sendStreamOriented(data: Data) {
        connection!.send(content: data, completion: .contentProcessed({ error in
            if error != nil {
                self.status = "Send Failed"
            }
        }))
    }

    func sendEndOfStream(connection: NWConnection) {
        connection.send(content: nil, contentContext: .defaultStream, isComplete: true, completion: .contentProcessed({ error in
            if error != nil {
                self.status = "Connection Failed"
            }
        }))
    }
    
    func getWiFiAddress() -> String? {
        var address : String?
        // Get list of all interfaces on the local machine:
        var ifaddr : UnsafeMutablePointer<ifaddrs>?
        guard getifaddrs(&ifaddr) == 0 else { return nil }
        guard let firstAddr = ifaddr else { return nil }

        // For each interface ...
        for ifptr in sequence(first: firstAddr, next: { $0.pointee.ifa_next }) {
            let interface = ifptr.pointee

            // Check for IPv4 or IPv6 interface:
            let addrFamily = interface.ifa_addr.pointee.sa_family
            if addrFamily == UInt8(AF_INET) || addrFamily == UInt8(AF_INET6) {

                // Check interface name:
                let name = String(cString: interface.ifa_name)
                if  name == "en0" {

                    // Convert interface address to a human readable string:
                    var hostname = [CChar](repeating: 0, count: Int(NI_MAXHOST))
                    getnameinfo(interface.ifa_addr, socklen_t(interface.ifa_addr.pointee.sa_len),
                                &hostname, socklen_t(hostname.count),
                                nil, socklen_t(0), NI_NUMERICHOST)
                    address = String(cString: hostname)
                }
            }
        }
        freeifaddrs(ifaddr)
        return address
    }
}
