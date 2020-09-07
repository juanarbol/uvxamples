#!/usr/local/bin/python3

# This is made for running the executables compiled.
from subprocess import call

import os

# Import the necessary packages
from consolemenu import *
from consolemenu.items import *

from pathlib import Path

# Create the menu
menu = ConsoleMenu("UVXAMPLES", "Learn libuv with code examples.")


def run_cpp_binding(name):
  call(["./build/%s" %name])

def build_menu():
  cpp_files = list(Path("./src").rglob("*.cc"))
  for file_name in cpp_files:
    extensionless_filename = file_name.name[:-3]
    function_item = FunctionItem("Run %s" %extensionless_filename,
                                run_cpp_binding,
                                [extensionless_filename])
    menu.append_item(function_item)


def print_menu():
  build_menu()
  menu.show()

print_menu()
