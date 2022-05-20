# Simulate a sports tournament

import csv
import sys
import random
import math

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    counts = {}

    # Read teams into memory from file
    with open(sys.argv[1]) as file:
        teams_file = csv.DictReader(file)

        for team in teams_file:
            # get team name and rating
            teams.append(team)

            # initialize wins of 0 per team
            counts[team["team"]] = 0

    # Simulate N tournaments and keep track of win counts
    for i in range(1000):
        # increment winner count
        counts[simulate_tournament(teams)] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((int(rating2) - int(rating1)) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""

    # iterate for total rounds
    for _round in range(int(math.log(len(teams), 2))):
        # iterate for games per round with step of 2
        teams = simulate_round(teams)

    # return winner
    return teams[0]["team"]


if __name__ == "__main__":
    main()
