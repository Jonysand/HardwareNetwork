//
//  ContentView.swift
//  netTools
//
//  Created by Yongkun Li on 2/13/20.
//  Copyright © 2020 Yongkun Li. All rights reserved.
//

import SwiftUI
import Network

struct ContentView: View {
    var NetWorkHelper = NetWorkTools()
    @State var remote_ip: String = "10.23.11.53"
    @State var remote_port: String = "10000"
    @State var data: String = ""
    
    var body: some View {
        NavigationView{
            List{
                HStack{
                    Text("Local IP address: ")
                    Spacer()
                    Text(NetWorkHelper.getWiFiAddress() ?? "not connected")
                }
                VStack(alignment: .leading){
                    Text("Remote IP:")
                    TextField("10.23.11.53", text: $remote_ip)
                }
                VStack(alignment: .leading){
                    Text("Port")
                    TextField("10000", text: $remote_port)
                        .keyboardType(.numberPad)
                }
                
                HStack{
                    Spacer()
                    Button("Connect TCP"){
                        self.NetWorkHelper.startTCP(host: self.remote_ip, port: Int(self.remote_port) ?? 80)
                    }.frame(height: 100)
                    Spacer()
                }
                
                HStack{
                    Text("Status")
                    Spacer()
                    Text(self.NetWorkHelper.status)
                }
                
                VStack(alignment: .leading){
                    Text("Data")
                    TextField("data", text: $data)
                }
                
                HStack{
                    Spacer()
                    Button("Send Data"){
                        self.NetWorkHelper.sendStreamOriented(data: self.data.data(using: .utf8) ?? Data.init())
                    }.frame(height: 100)
                    Spacer()
                }
                
            }.navigationBarTitle("TCP Client tool")
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
