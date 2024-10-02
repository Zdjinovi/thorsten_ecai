#include <cerrno>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

#include <getopt.h>
#include <math.h>

using namespace std;

int nodes, links, seed;
bool *graph;

/* Program options. */
static struct option long_options[] = {{"nodes", required_argument, 0, 'n'},
                                       {"links", required_argument, 0, 'l'},
                                       {"seed", required_argument, 0, 's'},
                                       {"help", no_argument, 0, '?'},
                                       {0, 0, 0, 0}};
static const char OPTION_STRING[] = "n:l:s:?";

/* Displays help. */
static void display_help(std::ostream &out) {
  out << "usage: generate-SA [options]" << std::endl
      << "options:" << std::endl
      << "  -n n, --nodes=n\t"
      << "number of nodes in the loop" << std::endl
      << "  -l l, --links=l\t"
      << "number of additionnal links" << std::endl
      << "  -s s, --seed=s\t"
      << "random number generator seed (if not using time)" << std::endl
      << "  -?     --help\t\t"
      << "display this help and exit" << std::endl
      << endl
      << endl
      << "Report bugs to < ... >." << endl;
}
void print_domain(std::ostream &out) {
  out << "(define (domain sysadmin-ssp)" << endl;
  out << "  (:requirements :probabilistic-effects :negative-preconditions "
         ":typing)"
      << endl;
  out << "  (:types computer - object)" << endl;
  out << "  (:constants ";
  for (int i = 0; i < nodes; i++)
    out << "computer" << i << " ";
  out << "- computer)" << endl;

  out << "  (:predicates " << endl
      << "    (running ?c - computer)" << endl
      << "    (rebooted ?c - computer)" << endl
      << "    (evaluate ?c - computer)" << endl
      << "    (update-status ?c - computer)" << endl
      << "    (one-off ?c - computer)" << endl
      << "    (all-on ?c - computer)" << endl
      << "    (all-updated)" << endl
      << "  )" << endl;

  out << "  (:action reboot" << endl
      << "    :parameters (?c - computer)" << endl
      << "    :precondition (all-updated)" << endl
      << "    :effect (and " << endl
      << "      (increase (total-cost) 1)" << endl
      << "      (not (all-updated))" << endl
      << "      (evaluate computer0)" << endl
      << "      (rebooted ?c)" << endl
      << "    )" << endl
      << "  )" << endl;

  for (int i = 0; i < nodes; ++i) {
    out << "  (:action evaluate-computer" << i << "-rebooted" << endl
        << "    :precondition (and" << endl
        << "      (evaluate computer" << i << ")" << endl
        << "      (rebooted computer" << i << ")" << endl
        << "    )" << endl
        << "    :effect (and " << endl
        << "      (not (evaluate computer" << i << "))" << endl;
    if (i != nodes - 1) {
      out << "      (evaluate computer" << i + 1 << ")" << endl;
    } else {
      out << "      (update-status computer0)" << endl;
    }
    out << "    )" << endl << "  )" << endl;

    out << "  (:action evaluate-computer" << i << "-all-on" << endl
        << "    :precondition (and" << endl
        << "      (evaluate computer" << i << ")" << endl
        << "      (not (rebooted computer" << i << "))" << endl;
    for (int j = 0; j != nodes; ++j) {
      if (graph[i + j * nodes]) {
        out << "      (running computer" << j << ")" << endl;
      }
    }
    out << "    )" << endl
        << "    :effect (and " << endl
        << "      (all-on computer" << i << ")" << endl
        << "      (not (evaluate computer" << i << "))" << endl;
    if (i != nodes - 1) {
      out << "      (evaluate computer" << i + 1 << ")" << endl;
    } else {
      out << "      (update-status computer0)" << endl;
    }
    out << "    )" << endl << "  )" << endl;

    for (int j = 0; j != nodes; ++j) {
      if (!graph[i + j * nodes]) {
        continue;
      }

      out << "  (:action evaluate-computer" << i << "-off-computer" << j << endl
          << "    :precondition (and" << endl
          << "      (evaluate computer" << i << ")" << endl
          << "      (not (rebooted computer" << i << "))" << endl
          << "      (not (running computer" << j << "))" << endl
          << "    )" << endl
          << "    :effect (and " << endl
          << "      (one-off computer" << i << ")" << endl
          << "      (not (evaluate computer" << i << "))" << endl;
      if (i != nodes - 1) {
        out << "      (evaluate computer" << i + 1 << ")" << endl;
      } else {
        out << "      (update-status computer0)" << endl;
      }
      out << "    )" << endl << "  )" << endl;
    }

    out << "  (:action update-status-computer" << i << "-rebooted" << endl
        << "    :precondition (and" << endl
        << "      (update-status computer" << i << ")" << endl
        << "      (rebooted computer" << i << ")" << endl
        << "    )" << endl
        << "    :effect (and " << endl
        << "      (not (update-status computer" << i << "))" << endl;
    if (i != nodes - 1) {
      out << "      (update-status computer" << i + 1 << ")" << endl;
    } else {
      out << "      (all-updated)" << endl;
    }
    out << "      (not (rebooted computer" << i << "))" << endl
        << "      (probabilistic 9/10 (running computer" << i << "))" << endl
        << "    )" << endl
        << "  )" << endl;

    out << "  (:action update-status-computer" << i << "-all-on" << endl
        << "    :precondition (and" << endl
        << "      (update-status computer" << i << ")" << endl
        << "      (not (rebooted computer" << i << "))" << endl
        << "      (all-on computer" << i << ")" << endl
        << "    )" << endl
        << "    :effect (and " << endl
        << "      (not (update-status computer" << i << "))" << endl;
    if (i != nodes - 1) {
      out << "      (update-status computer" << i + 1 << ")" << endl;
    } else {
      out << "      (all-updated)" << endl;
    }
    out << "      (not (all-on computer" << i << "))" << endl
        << "      (probabilistic 1/20 (not (running computer" << i << ")))" << endl
        << "    )" << endl
        << "  )" << endl;

    out << "  (:action update-status-computer" << i << "-one-off" << endl
        << "    :precondition (and" << endl
        << "      (update-status computer" << i << ")" << endl
        << "      (not (rebooted computer" << i << "))" << endl
        << "      (one-off computer" << i << ")" << endl
        << "    )" << endl
        << "    :effect (and " << endl
        << "      (not (update-status computer" << i << "))" << endl;
    if (i != nodes - 1) {
      out << "      (update-status computer" << i + 1 << ")" << endl;
    } else {
      out << "      (all-updated)" << endl;
    }
    out << "      (not (one-off computer" << i << "))" << endl
        << "      (probabilistic 1/4 (not (running computer" << i << ")))" << endl
        << "    )" << endl
        << "  )" << endl;
  }

  out << ")" << endl;
}

void print_problem(std::ostream &out) {
  out << "(define (problem sysadmin-ssp"
      << "-" << nodes << "-" << links << "-" << seed - (nodes + links) << ")"
      << endl
      << "  (:domain sysadmin-ssp)" << endl
      << "  (:init (all-updated))" << endl
      << "  (:goal (and" << endl
      << "    (all-updated)" << endl;
  for (int i = 0; i != nodes; ++i) {
    out << "    (running computer" << i << ")" << endl;
  }
  out << "  ))" << endl
      << "  (:metric minimize (total-cost))" << endl
      << ")" << endl;
}

int main(int argc, char **argv) {
  nodes = 5;
  links = 3;
  seed = time(NULL);

  try {
    /*
     * Get command line options.
     */
    while (1) {
      int option_index = 0;
      int c =
          getopt_long(argc, argv, OPTION_STRING, long_options, &option_index);
      if (c == -1) {
        break;
      }
      switch (c) {
      case 'n':
        nodes = atoi(optarg);
        break;
      case 'l':
        links = atoi(optarg);
        break;
      case 's':
        seed = atoi(optarg);
        break;
      case '?':
        display_help(std::cout);
        return 0;
      case ':':
      default:
        cerr << "Try `generate-SA --help' for more information." << endl;
        return -1;
      }
    }
    srandom(seed);

    if ((nodes <= 0) || (links < 0) || (links > nodes * (nodes - 2))) {
      cerr << "You need to specify n (>=1) and l (>=0 & <= n^2-2n)." << endl;
      return -1;
    }

    seed += nodes + links;

    if (optind < argc) {
      cerr << "There seems to be too many \"free\" arguments..." << endl;
      return -1;
    }

    /**
     * Lets create a table of links (i.e. the graph)
     */

    graph = (bool *)malloc(nodes * nodes * sizeof(bool));
    // Default: no link between two nodes
    for (int i = 0; i < nodes; i++)
      for (int j = 0; j < nodes; j++)
        graph[i + j * nodes] = false;

    // Create oriented ring: link i with i+1
    for (int i = 0; i < (nodes - 1); i++)
      graph[i + (i + 1) * nodes] = true;
    graph[(nodes - 1) + 0 * nodes] = true;

    // Add random links everywhere else (not on the diagonal though)
    for (int k = 0; k < links; k++) {
      bool found = false;
      do {
        int i = random() % nodes;
        int j = random() % (nodes - 2);
        j = (i + j + 2) % nodes;
        if (graph[i + j * nodes] == false) {
          graph[i + j * nodes] = true;
          found = true;
        }
      } while (found == false);
    }

    print_domain(std::cout);
    print_problem(std::cerr);
  } catch (const exception &e) {
    cerr << endl << "generate-SA: " << e.what() << endl;
    return 1;
  } catch (...) {
    cerr << "generate-SA: fatal error" << endl;
    return -1;
  }

  return 0;
}
