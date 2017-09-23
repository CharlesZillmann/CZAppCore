//
//  main.cpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/5/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#include <iostream>
#include "CZAppCoreCSVFile.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    CSVFile myCSVFile("/Users/zillmann/Documents/testdata.csv",1,2, 0x0D);
    myCSVFile.DumpColumnTitles();
    myCSVFile.DumpAllRows();
    myCSVFile.DumpColumn(0);
    std::cout << myCSVFile.FindRowByValue("206",0);
    std::cout << "\n";
    std::cout << myCSVFile.GetNeighborValue("206", 0, 1);
    std::cout << ",";
    std::cout << myCSVFile.GetNeighborValue("206", 0, 2);
    std::cout << "\n";
    
    CSVFile myCSV2File("/Users/zillmann/Documents/testdata2.csv",1,2, 0x0D);
    myCSV2File.DumpColumnTitles();
	myCSV2File.DumpAllRows();
    myCSV2File.DumpColumn(0);
    std::cout << "\n";
    std::cout << myCSV2File.FindRowByValue("206",0);
    std::cout << "\n";
    std::cout << myCSV2File.GetNeighborValue("206",0,1);
    std::cout << ",";
    std::cout << myCSV2File.GetNeighborValue("206",0,2);
    std::cout << "\n";
    std::cout << "Hello, World!\n";
    //AppCoreArgs           Construct (int argc, const char * argv[])
    //AppCoreError          Construct (Args)
    //AppCoreHostProfile    Construct (Args, Error)
    //AppCoreMessages       Construct (Args, Error, HostProfile)
    //AppCoreIniFile        Construct (Args, Error, HostProfile, Messages)
    //AppCoreStorage        Construct (Args, Error, HostProfile, Messages, IniFile)
    //AppCoreProcess        Construct (Args, Error, HostProfile, Messages, IniFile, Storage)
    
    //AppCoreProcess        ProcessStorage (Args, Error, HostProfile, Messages, IniFile, Storage)
    
    //AppCoreProcess        Destruct (Void)
    //AppCoreStorage        Destruct (Void)
    //AppCoreIniFile        Destruct (Void)
    //AppCoreMessages       Destruct (Void)
    //AppCoreHostProfile    Destruct (Void)
    //AppCoreError          Destruct (Void)
    //AppCoreArgs           Destruct (Void)
    return 0;
}

//ACI CREDENTIALS.py
//apic_ip_address = ""   # Do not delete leave empty if you use offline mode
//apic_admin_user =""   # Do not delete leave empty if you use offline mode
//apic_admin_password =""# Do not delete leave empty if you use offline mode
//input_excel_file = "demo_data_2.xlsx"
//fabric_template_path = "./templates/"
//execution_mode = "offline"   # Possible choices are   offline  or online


//################################################################################
//#                === Deploy ACI From EXCEL   ===                               #
//#                ===         DAFE             ===                               #
//################################################################################
//#                                                                              #
//# [+] Written by:                                                              #
//#  |_ Fabrice Dall'ara (fadallar@cisco.com)                                    #
//#  |_ Cloud & Software Services
//#  |_ Cisco Advanced Services, EMEAR.                                          #
//#                                                                              #
//################################################################################
//#                                                                              #
//# Copyright (c) 2015 Cisco Systems                                             #
//# All Rights Reserved.                                                         #
//#                                                                              #
//#    Unless required by applicable law or agreed to in writing, this software  #
//#    is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF   #
//#    ANY KIND, either expressed or implied.                                    #
//#                                                                               #
//#  And do not forget :  " DONE IS BETTER THAN PERFECT !!!!! "                   #
//#                                                                              #
//################################################################################
//
//import os
//import requests
//import openpyxl
//import warnings
//import aci_credentials as aci
//import jinja2
//import sys
//import time
//from jinja2 import Environment, FileSystemLoader
//from xml.dom import minidom
//requests.packages.urllib3.disable_warnings()   # Disable urllib3 warning when https is used with self-signed certificate
//warnings.filterwarnings("ignore")  # Disable warning message logged by openpyxl
//
//"""
//"""
//
//APIC_IP = aci.apic_ip_address
//APIC_ADMIN = aci.apic_admin_user
//APIC_ADMIN_PASS = aci.apic_admin_password
//EXCEL_FILE = aci.input_excel_file
//TEMPLATE_PATH = aci.fabric_template_path
//LOGFILE = "dafe_execution.log"
//EXECUTION_MODE = aci.execution_mode
//
//class ACIXmlParser(object):
//"""
//This class provides the required method to build a consolidated
//ACI XML tree out of multiple XML files
//"""
//def get_xml_root(self, xml_string):
//"""
//Takes as argument an xml formated string
//Returns XML Root Node
//"""
//xml_input = minidom.parseString(xml_string)
//root = xml_input.childNodes[0]
//return root
//
//def get_element_key_attributes(self, element):
//"""
//Takes as argument
//* element a minidom Element
//Returns a list of string containing value of Element attribute
//name,dn,tDN used to identifies unique ACI object
//vendor has been added in the list in order to group VMM provider by group
//"""
//element_name = element.getAttribute("name")
//element_dn = element.getAttribute("dn")
//element_tdn = element.getAttribute("tDn")
//element_vendor = element.getAttribute("vendor")   # for VMM Provider root tag
//attribute_list = [element_name, element_dn, element_tdn, element_vendor]
//element_keys = []
//for attribute in attribute_list:
//if attribute:
//element_keys.append(attribute)
//return element_keys
//

//**********************************
//def insert_xml_element(self, master_root, data_root):
//"""
//Recursive function whose is goal is to merge two XML document
//Takes as argument
//*  master_root  type(minidom element) which represents root of
//current branch in the target (master) XML tree
//* data_root  type(minidom element) which represents the root of
//the current branch in the data XML tree that need to be merged with the master tree
//Returns  a new master_root of type(minidom elemen) which is the result of merge
//"""
//for childNode in data_root.childNodes:
//if childNode.nodeType == 1:  # Element Node only
//found = False
//node_tag = childNode.tagName
//master_elements = master_root.getElementsByTagName(node_tag)
//# Do not consider top element like infraInfra which has no attribute
//if childNode.hasAttributes():
//node_keys = self.get_element_key_attributes(childNode)
//if len(master_elements) != 0:
//for element in master_elements:
//element_keys = self.get_element_key_attributes(element)
//if set(node_keys) & set(element_keys):
//found = True
//if childNode.hasChildNodes():
//self.insert_xml_element(element, childNode)
//break
//elif len(master_elements) != 0:  # Consider top element like infraInfra
//found = True
//for element in master_elements:
//if childNode.hasChildNodes():
//self.insert_xml_element(element, childNode)
//break
//if not found:
//master_root.appendChild(childNode)
//return master_root

//**********************************
//
//def create_offline_xml_output(self, master_root, data_root):
//"""
//"""
//master_root = self.insert_xml_element(master_root, data_root)
//return master_root
//

//**********************************
//def generate_xml_per_top_level_class(self, root_node):
//""" Quick hack to create an XML file per child of polUni
//This in order to be able to upload the file from the APIC GUI or other post method
//"""
//LOG.print_message("+--- Generating consolidated XML files ")
//top_tag_list = ["fvTenant", "ctrlrInst", "infraInfra", "l3extDomP", "vmmProvP", "physDomP", "l2extDomP", "fabricInst"]
//xml_doc = minidom.Document()
//xml_doc.appendChild(root_node)
//for tag_name in top_tag_list:
//element_list = xml_doc.getElementsByTagName(tag_name)
//for element in element_list:
//xml_root = "<polUni></polUni>"
//new_doc = minidom.Document()
//pol_uni_root = self.get_xml_root(xml_root)  #creates a polUni Element
//output_xml_file_name = element.tagName
//if element.hasAttribute("name"):
//output_xml_file_name = output_xml_file_name + "-" + element.getAttribute("name")+".xml"
//elif element.hasAttribute("vendor"):  #covers VMMDom
//output_xml_file_name = output_xml_file_name + "-" + element.getAttribute("vendor")+".xml"
//else:
//output_xml_file_name = output_xml_file_name+".xml"
//pol_uni_root.appendChild(element)
//new_doc.appendChild(pol_uni_root)
//xml_logging = OutputLogging(output_xml_file_name)
//xml_logging.print_string_to_file(new_doc.toprettyxml())
//

//**********************************
//def build_consolidated_xml(self, xml_files_list):
//""" Creates a single consolidated xml Document
//"""
//xml_root = "<polUni></polUni>"
//xml_doc = minidom.Document()
//master_root = self.get_xml_root(xml_root)
//for xml_file in xml_files_list:
//data_root = self.get_xml_root(xml_file)
//master_root = self.create_offline_xml_output(master_root, data_root)
//self.generate_xml_per_top_level_class(master_root)
//
//

//**********************************
//class ACIException(Exception):
//"""
//Exception Class
//Not currently used but will be shortly
//"""

//**********************************
//def fatal(self, msg):
//"""
//Prints and error message and aborts program execution
//"""
//sys.stderr.write(msg+"\n")
//sys.exit(1)
//

//**********************************
//def warning(self, msg):
//"""
//Prints a warning message to stderr
//"""
//sys.stderr.write(msg+"\n")
//
//

//**********************************
//class OutputLogging(object):
//"""
//Output Logging
//Used to print to STDOUT and or LOGFILE
//Print to stdout will be enhanced in order to pretty print the messages
//"""

//**********************************
//def __init__(self, file_name):
//now = time.time()
//local_time = time.localtime(now)
//timestamp = time.strftime("%Y-%m-%d-%H%M", local_time)
//if not os.path.exists(timestamp):
//os.mkdir(timestamp)
//self.output_file = os.path.join(timestamp, file_name)
//self.output = open(self.output_file, "a")
//

//**********************************
//def print_string_to_file(self, message):
//self.output.write(message+"\n")
//

//**********************************
//def print_to_stdout(self, message):
//print message
//

//**********************************
//def print_message(self, message):
//"""
//Print message to both STDOUT and output Logfile
//"""
//self.print_to_stdout(message)
//self.print_string_to_file(message)
//
//LOG = OutputLogging(LOGFILE)
//ACIERROR = ACIException()
//

//**********************************
//class Session(object):
//""" Helper function which handles http authentication and http post request to
//https://{apic_ip}/api/policymgr/mo/.xml
//http authentication is part of the Session class constructor
//http post is provided by public apic_xml_post method
//"""

//**********************************
//def __init__(self, apic_ip, user, passwd):
//self.ip = apic_ip
//self.user = user
//self.passwd = passwd
//self.cookie = self.get_cookie()
//

//**********************************
//def get_cookie(self):
//try:
//auth_url = "https://%s/api/mo/aaaLogin.xml" % self.ip
//auth_xml = "<aaaUser name='%s' pwd ='%s'/>" % (self.user, self.passwd)
//LOG.print_message("Getting cookie from %s" % self.ip)
//session = requests.post(auth_url, data=auth_xml, verify=False, timeout=5)
//return session.cookies
//except requests.exceptions.Timeout:
//ACIERROR.fatal("APIC %s timed out " % (self.ip))
//except requests.exceptions.ConnectionError:
//ACIERROR.fatal("Connection error can't logging to APIC %s with user %s" % (self.ip, self.user))
//

//**********************************
//def apic_xml_post(self, xmldata):
//xmlpost_url = "https://%s/api/policymgr/mo/.xml" % self.ip
//xmlpost = requests.post(xmlpost_url, data=xmldata, cookies=self.cookie, verify=False)
//if xmlpost.status_code != 200:
//return xmlpost.text
//else:
//return 200
//
//

//**********************************
//class InputData(object):
//

//**********************************
//def open_excel_workbook(self, file_name):
//""" Takes file name as input and return a openpyxl workbook object
//@param file_name : excel source file name
//@return workbook : openpyxl workbook object
//"""
//try:
//LOG.print_message("Opening excel workbook %s" % file_name)
//workbook = openpyxl.load_workbook(file_name, data_only=True) #data_only = True is used to load cell data value only not formula
//return workbook
//except IOError as e:
//ACIERROR.fatal("IOError Can't Open file %s" %file_name)
//except:
//ACIERROR.fatal("Undefined error opening excel %s data input" %file_name)
//

//**********************************
//def get_build_tasks(self, workbook, sheet_name):
//"""
//"""
//active_sheet = workbook.get_sheet_by_name(sheet_name)
//LOG.print_message("+---------- Creating Build tasks ----------+")
//task_lists = []
//for row_num in range(2, active_sheet.max_row+1):
//if active_sheet.cell(row=row_num, column=1).value == "yes":
//new_entry = []
//for col_num in range(2, active_sheet.max_column+1):
//new_entry.append(active_sheet.cell(row=row_num, column=col_num).value)
//LOG.print_message("+ " + new_entry[0])
//task_lists.append(new_entry)
//LOG.print_message("+------------------------------------------+")
//return task_lists
//

//**********************************
//def excel_to_dictionary(self, workbook, sheet_name):
//""" Takes a workbook and a worksheet name as input return a dictionary with the following structure
//{sheet_name:[{},{},...]}
//"""
//LOG.print_message("+- Importing worksheet %s" % sheet_name)
//active_sheet = workbook.get_sheet_by_name(sheet_name)
//active_dict = {}
//active_dict[sheet_name] = []
//header = []
//for col_num in range(1, active_sheet.max_column+1):
//header.append(active_sheet.cell(row=1, column=col_num).value)
//for row_num in range(2, active_sheet.max_row+1):
//new_entry = {}
//for col_num in range(1, active_sheet.max_column+1):
//if active_sheet.cell(row=row_num, column=col_num).value != None:
//new_entry[header[col_num-1]] = str(active_sheet.cell(row=row_num, column=col_num).value).lstrip().rstrip()
//else:
//new_entry[header[col_num-1]] = ""
//active_dict[sheet_name].append(new_entry)
//return active_dict
//
//

//**********************************
//class TemplateRender(object):
//""" Template rendering Class which use jinja2 Templating language
//The class constructor takes the path to the xml template directory as input data
//The file names in the directory are loaded in a dictionary structure
//The class provides the  method render_template for rendering a template
//"""

//**********************************
//def __init__(self, template_path):
//self.jinja_env = self.create_jinja_env(template_path)
//self.template_dict = self.load_template(template_path)
//

//**********************************
//def create_jinja_env(self, template_path):
//template_loader = FileSystemLoader(searchpath=template_path)
//template_env = Environment(loader=template_loader, trim_blocks=True, lstrip_blocks=True)
//return template_env
//

//**********************************
//def load_template(self, template_path):
//try:
//template_dict = {}
//files = os.listdir(template_path)
//for template in files:
//filename = template.split(".")
//fo = open(template_path+template, "r")
//template_dict[filename[0]] = fo.read()
//return template_dict
//except OSError as e:
//ACIERROR.fatal("ERROR: Can't find template directory %s " %template_path)
//sys.exit(1)
//except:
//ACIERROR.fatal("ERROR: Undefined error in loading template")
//

//**********************************
//def render_template(self, template_file, item):
//""" Takes as argument
//The name of the template file to be used : template_file
//"""
//try:
//template = self.jinja_env.get_template(template_file)
//xml_data = template.render(config=item)
//return xml_data
//except jinja2.TemplateNotFound as e:
//ACIERROR.fatal("ERROR: can't find template file %s" % template_file)
//except jinja2.TemplateSyntaxError as e:
//message = "ERROR: Syntax Error in Template %s " % template_file
//error_line = str(e.message) + " line number : " + str(e.lineno)
//ACIERROR.warning(message + " " + error_line)
//except:
//ACIERROR.warning(" Undefined error while rendering template %s" %template_file)
//
//

//**********************************
//class FabricBuild(object):
//""" Takes as argument
//The path to the template file folder : template_path
//The name of the input data excel file : input_file
//A Session object for the fabric to be configured : aci_fabric
//"""
//def __init__(self, template_path, input_file, execution_mode):
//self.fabric_template = TemplateRender(template_path)
//self.input_data = InputData()
//self.workbook = self.input_data.open_excel_workbook(input_file)
//self.build_tasks = self.input_data.get_build_tasks(self.workbook, "build_tasks")
//accept_build_tasks = raw_input(" Do you want to proceed with the above configuration tasks y/n ? [n] : ")
//if accept_build_tasks == "y":
//LOG.print_message("Proceeding....")
//self.build_fabric(self.build_tasks, execution_mode)
//else:
//LOG.print_message("Aborting configuration")
//

//**********************************
//def get_state_mode(self, data_dictionary):
//""" Planned for future feature   deleting ignoring specific lines in the excel worksheet
//"""
//try:
//mode = data_dictionary['status']
//if mode == "deleted":
//action = "deleting"
//elif mode == "ignored":
//action = "skipping"
//else:
//action = "creating"
//return action
//except:
//action = "creating"
//return action
//

//**********************************
//def build_fabric(self, build_tasks, execution_mode):
//""" Fabric Configuration Logic
//"""
//xml_files_list = []
//if execution_mode == "online":
//my_fabric = Session(APIC_IP, APIC_ADMIN, APIC_ADMIN_PASS)
//if my_fabric.cookie:
//got_cookie = True
//else:
//LOG.print_message("+--- wConnection Error : Fabric configuration aborted, reverting to offline XML generation mode ")
//got_cookie = False
//else:
//got_cookie = False
//for task in build_tasks:
//object_type, worksheet_name, template_file_name = task[:3]
//datadict = self.input_data.excel_to_dictionary(self.workbook, worksheet_name)
//try:
//message = "+--- Generating %s" % object_type
//LOG.print_message(message)
//for item in datadict[worksheet_name]:
//action = self.get_state_mode(item)
//if action != "skipping":
//xml_data = self.fabric_template.render_template(template_file_name, item)
//if xml_data:
//xml_files_list.append(xml_data)
//if got_cookie:
//post_answer = my_fabric.apic_xml_post(xml_data)
//if post_answer != 200:
//LOG.print_message('+--- Error %s %s %s' % (action, object_type, item['name']))
//LOG.print_message(post_answer)
//else:
//LOG.print_message('+--- Successfully %s %s %s' % (action, object_type, item['name']))
//else:
//LOG.print_message("+--- Can't generate XML for %s %s" % (object_type, item['name']))
//else:
//LOG.print_message("+--- Skipping %s %s" % (object_type, item['name']))
//except:
//ACIERROR.fatal("+--- Undefined error quitting DAFE ")
//xmlParse = ACIXmlParser()
//xmlParse.build_consolidated_xml(xml_files_list)
//
//
//if EXECUTION_MODE == "online":
//message = "Warning: You have selected online configuration  mode the configuration will be pushed to APIC %s" %APIC_IP
//LOG.print_message(message)
//ok_to_push_config = raw_input("Are you sure you want to push this config  y/n ? [n]: ")
//if ok_to_push_config == "y":
//FabricBuild(TEMPLATE_PATH, EXCEL_FILE, "online")
//else:
//LOG.print_message("Reverting to offline mode")
//FabricBuild(TEMPLATE_PATH, EXCEL_FILE, "offline")
//elif EXECUTION_MODE == "offline":
//FabricBuild(TEMPLATE_PATH, EXCEL_FILE, "offline")
//else:
//LOG.print_message("Error: Abort configuration, execution mode incorrect correct values are online or offline ")

