# Network Testing Suite

The Network Testing Suite (NTS) is a tool designed to test the network implementation of a piece of software. It allows the developer to write comprehensive tests to validate the requirements of the program from the outside and to account for unusual cases.

The main features that the NTS provides to the tester are:

- Several communication protocols to communicate with the program, including UDP, TCP and ICMP.

- Extensible testing framework setup that implements the most common test cases in order to write accessible tests, simple or extensive, and accommodate additional needs. These include:

  - Message builders that simplify the tedious process of creating complex messages in just a few steps;

  - Messengers that allow the developer to specify patterns for communicating with the program and avoid endless callback chains;

  - Sessions that handle the communication between endpoints and manage the messages sent and received during each test.
