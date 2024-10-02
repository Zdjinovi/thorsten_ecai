
/* Created by Robert Givan and Sungwook Yoon */
/* Modified by Olivier Buffet for the purpose of IPC-2008 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int gnum_classes = 2;
int gnum_units = 2;
int gnum_plan_length = 1000;
int gnum_prob_c0 = 3;

int gnum_packets;
int gnum_add_packages = 0;

int greclaim_cost = 5;

char gproblem_name[256];

void print_domain() {
  int i, j;
  int cur_prob;

  fprintf(stderr, "(define (domain %s-dom)\n", gproblem_name);
  fprintf(stderr, " (:requirements :probabilistic-effects "
                  ":negative-preconditions :typing)\n");
  fprintf(stderr, " (:types class packet timestep phase)\n");

  /* constants printing */
  fprintf(stderr, " (:constants \n");
  fprintf(stderr, "    ");
  for (i = 0; i < gnum_classes; i++) {
    fprintf(stderr, "%c%d ", 'C', i);
  }
  fprintf(stderr, "- class\n");
  fprintf(stderr, "    ");
  for (i = 0; i < gnum_units + 1; i++) {
    fprintf(stderr, "%c%d ", 'U', i);
  }
  fprintf(stderr, "- timestep\n");
  fprintf(stderr, "    ");
  for (i = 0; i < gnum_packets + 1; i++) {
    fprintf(stderr, "%c%d ", 'P', i);
  }
  fprintf(stderr, "- packet\n");
  fprintf(stderr, "    Arrivals-and-updating Cleanup-and-service - phase\n");
  fprintf(stderr, " )\n");

  /* predciates definition printing */
  fprintf(stderr, " (:predicates\n");
  fprintf(stderr, "   (current-phase ?s - phase)\n");
  fprintf(stderr, "   (packet-class ?p - packet ?c - class)\n");
  fprintf(stderr, "   (time-to-live ?p - packet ?t - timestep)\n");
  fprintf(stderr, "   (available ?p - packet)\n");
  fprintf(stderr, "   (current-timestep ?t - timestep)\n");
  fprintf(stderr, "   (next-timestep ?t0 ?t1 - timestep)\n");
  fprintf(stderr, "   (need-to-process-arrivals ?c - class)\n");
  fprintf(stderr, "   (served ?c - class)\n");
  fprintf(stderr, " )\n");

  /* action definition printing, changes with parameters */
  fprintf(stderr, " (:action process-arrivals-C0\n");
  fprintf(stderr, "  :parameters (?arriving-packet - packet ?t - timestep)\n");
  fprintf(stderr, "  :precondition (and\n");
  fprintf(stderr,
          "                    (current-phase Arrivals-and-updating)\n");
  fprintf(stderr, "                    (available ?arriving-packet)\n");
  fprintf(stderr, "                    (need-to-process-arrivals C0)\n");
  fprintf(stderr, "                    (current-timestep ?t)\n");
  fprintf(stderr, "                )\n");
  fprintf(stderr, "  :effect (and\n");
  fprintf(stderr, "              (not (need-to-process-arrivals C0))\n");
  fprintf(stderr, "              (probabilistic %d/1000\n", gnum_prob_c0);
  fprintf(
      stderr,
      "                            (and (not (available ?arriving-packet))\n");
  fprintf(
      stderr,
      "                                 (packet-class ?arriving-packet C0)\n");
  fprintf(
      stderr,
      "                                 (time-to-live ?arriving-packet ?t)\n");
  fprintf(stderr, "                            )\n");
  fprintf(stderr, "              )\n");
  fprintf(stderr, "              (increase (total-cost) 1)\n");
  fprintf(stderr, "          )\n");
  fprintf(stderr, " )\n");

  if (gnum_classes != 1) {
    fprintf(stderr, " (:action process-arrivals\n");
    fprintf(stderr, "  :parameters (?arriving-packet - packet ?c - class ?t - timestep)\n");
    fprintf(stderr, "  :precondition (and\n");
    fprintf(stderr, "                    (not (= ?c C0))\n");
    fprintf(stderr,
            "                    (current-phase Arrivals-and-updating)\n");
    fprintf(stderr, "                    (available ?arriving-packet)\n");
    fprintf(stderr, "                    (need-to-process-arrivals ?c)\n");
    fprintf(stderr, "                    (current-timestep ?t)\n");
    fprintf(stderr, "            )\n");
    fprintf(stderr, "  :effect (and\n");
    fprintf(stderr, "             (not (need-to-process-arrivals ?c))\n");

    if (gnum_classes > 2) {
      fprintf(stderr, "             (probabilistic 110/%d\n",
              100 * (gnum_classes - 1));
      fprintf(stderr, "                              (and (not (available "
                      "?arriving-packet))\n");
      fprintf(stderr, "                                   (packet-class "
                      "?arriving-packet ?c)\n");
      fprintf(stderr, "                                   (time-to-live "
                      "?arriving-packet ?t)\n");
      fprintf(stderr, "                              )\n");
      fprintf(stderr, "             )\n");
    } else if (gnum_classes == 2) {
      fprintf(stderr, "             (not (available ?arriving-packet))\n");
      fprintf(stderr, "             (packet-class ?arriving-packet ?c)\n");
      fprintf(stderr, "             (time-to-live ?arriving-packet ?t)\n");
    }
    fprintf(stderr, "             (increase (total-cost) 1)\n");
    fprintf(stderr, "          )\n");
    fprintf(stderr, " )\n");
  }

  fprintf(stderr, " (:action time-update\n");
  fprintf(stderr, " :parameters (?t0 ?t1 - timestep)\n");
  fprintf(stderr, " :precondition (and\n");
  fprintf(stderr, "                   (current-phase Arrivals-and-updating)\n");
  fprintf(stderr, "                   (current-timestep ?t0)\n");
  fprintf(stderr, "                   (next-timestep ?t0 ?t1)\n");
  for (i = 0; i < gnum_classes; i++) {
    fprintf(stderr, "                   (not (need-to-process-arrivals C%d))\n",
            i);
  }
  fprintf(stderr, "               )\n");
  fprintf(stderr, " :effect (and \n");
  fprintf(stderr, "            (not (current-phase Arrivals-and-updating))\n");
  fprintf(stderr, "            (current-phase Cleanup-and-service)\n");
  fprintf(stderr, "            (not (current-timestep ?t0))\n");
  fprintf(stderr, "            (current-timestep ?t1)\n");
  fprintf(stderr, "            (increase (total-cost) 1)\n");
  fprintf(stderr, "         )\n");
  fprintf(stderr, " )\n");

  cur_prob = 1;

  for (i = 0; i != gnum_classes; ++i) {
    fprintf(stderr, " (:action reclaim-packet-C%d\n", i);
    fprintf(stderr, "  :parameters (?p - packet ?t - timestep)\n");
    fprintf(stderr, "  :precondition (and\n");
    fprintf(stderr,
            "                    (current-phase Cleanup-and-service)\n");
    fprintf(stderr, "                    (packet-class ?p C%d)\n", i);
    fprintf(stderr, "                    (time-to-live ?p ?t)\n");
    fprintf(stderr, "                )\n");
    fprintf(stderr, "  :effect (and\n");
    fprintf(stderr, "              (not (time-to-live ?p ?t))\n");
    fprintf(stderr, "              (not (packet-class ?p C%d))\n", i);
    fprintf(stderr, "              (available ?p)\n");
    fprintf(stderr, "              (increase (total-cost) %d)\n", greclaim_cost);
    fprintf(stderr, "          )\n");
    fprintf(stderr, " )\n");
  }

  fprintf(stderr, " (:action packet-serve\n");
  fprintf(stderr, "  :parameters (?p - packet ?c - class ?t - timestep)\n");
  fprintf(stderr, "  :precondition (and\n");
  fprintf(stderr, "                    (current-phase Cleanup-and-service)\n");
  fprintf(stderr, "                    (packet-class ?p ?c)\n");
  fprintf(stderr, "                    (current-timestep ?t)\n");
  for (i = 0; i != gnum_packets; ++i) {
    fprintf(stderr, "                    (not (time-to-live P%d ?t))\n", i);
  }
  fprintf(stderr, "                )\n");
  fprintf(stderr, "  :effect (and\n");
  fprintf(
      stderr,
      "              (forall (?c1 - class) (need-to-process-arrivals ?c1))\n");
  fprintf(
      stderr,
      "              (forall (?u - timestep) (not (time-to-live ?p ?u)))\n");
  fprintf(stderr, "              (not (current-phase Cleanup-and-service))\n");
  fprintf(stderr, "              (current-phase Arrivals-and-updating)\n");
  fprintf(stderr, "              (served ?c)\n");
  fprintf(stderr, "              (not (packet-class ?p ?c))\n");
  fprintf(stderr, "              (available ?p)\n");
  fprintf(stderr, "              (increase (total-cost) 1)\n");
  fprintf(stderr, "          )\n");
  fprintf(stderr, " )\n");

  fprintf(stderr, " (:action serve-nothing\n");
  fprintf(stderr, "  :parameters (?t - timestep)\n");
  fprintf(stderr, "  :precondition (and\n");
  fprintf(stderr, "                    (current-phase Cleanup-and-service)\n");
  fprintf(stderr, "                    (current-timestep ?t)\n");
  for (i = 0; i != gnum_packets; ++i) {
    fprintf(stderr, "                    (not (time-to-live P%d ?t))\n", i);
  }
  fprintf(stderr, "                )\n");
  fprintf(stderr, "  :effect (and    \n");
  fprintf(
      stderr,
      "              (forall (?c1 - class) (need-to-process-arrivals ?c1))\n");
  fprintf(stderr, "              (not (current-phase Cleanup-and-service))\n");
  fprintf(stderr, "              (current-phase Arrivals-and-updating)\n");
  fprintf(stderr, "              (increase (total-cost) 1)\n");
  fprintf(stderr, "          )\n");
  fprintf(stderr, " )\n");
  fprintf(stderr, ")\n");
}

void print_problem() {
  int i, j;

  fprintf(stdout, "(define (problem %s)\n", gproblem_name);
  fprintf(stdout, "  (:domain %s-dom)\n", gproblem_name);
  fprintf(stdout, "  (:objects )\n");
  fprintf(stdout, "  (:init \n");
  fprintf(stdout, "         (current-phase Arrivals-and-updating)\n");
  fprintf(stdout, "         (current-timestep U0)\n");
  for (i = 0; i < gnum_classes; i++)
    fprintf(stdout, "         (need-to-process-arrivals C%d)\n", i);
  for (i = 0; i < gnum_packets; i++)
    fprintf(stdout, "         (available P%d)\n", i);
  for (i = 0; i < gnum_units + 1; i++) {
    fprintf(stdout, "         (next-timestep U%d U%d)\n", i,
            (i + 1) % (gnum_units + 1));
  }
  fprintf(stdout, "  )\n");

  fprintf(stdout, "  (:goal (and\n");
  for (i = 0; i < gnum_classes; i++) {
    fprintf(stdout, "      (served C%d)\n", i);
  }
  fprintf(stdout, "  ))\n");
  fprintf(stdout, "  (:metric minimize (total-cost))\n");
  fprintf(stdout, ")\n");
}

int process_command_line(int argc, char *argv[])
{
  char option;

  while (--argc && ++argv) {
    if (*argv[0] != '-' || strlen(*argv) != 2) {
      return 0;
    }
    option = *++argv[0];
    switch (option) {
    default:
      if (--argc && ++argv) {
        switch (option) {

        case 'c':
          sscanf(*argv, "%d", &gnum_classes);
          break;
        case 'u':
          sscanf(*argv, "%d", &gnum_units);
          break;
        case 'l':
          sscanf(*argv, "%d", &gnum_plan_length);
          break;
        case 'n':
          sscanf(*argv, "%s", gproblem_name);
          break;
        case 'p':
          sscanf(*argv, "%d", &gnum_add_packages);
          break;
        case 'r':
          sscanf(*argv, "%d", &greclaim_cost);
          break;

        default:
          fprintf(stderr, "\nschedule: unknown option: %c entered\n\n", option);
          return 0;
        }
      } else {
        return 0;
      }
    }
  }

  return 1;
}

int main(int argc, char *argv[]) {
  /* randomize */
  srand((unsigned int)getpid());

  /* read in command arguments */
  if (!process_command_line(argc, argv)) {
    fprintf(stderr, "example: schedule -c 2 -u 2 -l 1000 -p 0 -r 5\n");
    exit(1);
  }

  if (gnum_plan_length < 15) {
    fprintf(stderr, "increase plan length to more than 15");
    exit(2);
  }

  if (gnum_units < gnum_classes) {
    fprintf(stderr, "Number of units must be less or equal to number of classes!\n");
    exit(2);
  }

  gnum_packets = gnum_classes + gnum_add_packages;

  gnum_prob_c0 =
      (int)((float)1000 *
            ((float)1 / (((float)(gnum_plan_length - 5 * (gnum_classes - 1))) /
                         (float)(gnum_classes + 2))));

  print_domain();
  /*create_a_problem();*/
  print_problem();
}
