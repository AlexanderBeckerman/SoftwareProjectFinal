import numpy as np
import pandas as pd
import sys
from spkmeans import *

def main():
    np.random.seed(0)

    if len(sys.argv) == 4:

        k = sys.argv[1]
        if not k.isnumeric() or not int(k) == float(k):
            print("An error has occured!")
            exit()
        k = int(k)
        goal = sys.argv[2]
        file = sys.argv[3]

    elif len(sys.argv) == 3:
        k = -1  # default value
        goal = sys.argv[1]
        file = sys.argv[2]
    else:
        print("Invalid number of arguments")
        exit()

    df = pd.read_csv(file, sep=",", header=None)
    vectors = df.to_numpy()
    numPoints = vectors.shape[0]
    vectors = vectors.tolist()

    if goal != "jacobi":
        if goal == "wam":
            wam(file)
        elif goal == "ddg":
            ddg(file)
        elif goal == "gl":
            gl(file)
        elif goal == "jacobi":
            jacobi(file)
        elif goal == "spk":
            vectors = spk(file, k)
            k = len(vectors[0]) #each vectors is a point in R^k
            centroids, centroids_indexes = kmeans_pp(vectors, k)
            dim = len(centroids[0])
            for i in range(len(centroids_indexes)):
                if (i != len(centroids_indexes) - 1):
                    print(centroids_indexes[i], end=",")
                else:
                    print(centroids_indexes[i])
            s = kmeans(300, 0, dim, centroids, vectors)


def kmeans_pp(vectors, k):
    np.random.seed(0)
    count = 0
    num_rows, num_cols = vectors.shape
    ind = np.random.choice(vectors.shape[0])
    centroids = [vectors[ind].tolist()]
    probabilities = [0 for i in range(num_rows)]
    chosen_indexes = [ind]
    mindist = -1

    while len(centroids) < k:

        distances = [0 for i in range(num_rows)]
        dist_sum = 0

        for row in vectors:  # calculate step 2
            if count == ind or count in chosen_indexes:  # if curr index is a centroid
                count += 1
                continue
            else:
                for cent in centroids:
                    if mindist != -1:
                        mindist = min(mindist, np.linalg.norm(np.array(row) - np.array(cent)))
                    else:
                        mindist = np.linalg.norm(np.array(row) - np.array(cent))
                distances[count] = mindist
                dist_sum += mindist
                mindist = -1
            count += 1
        count = 0
        for i in range(len(probabilities)):
            probabilities[i] = distances[i] / dist_sum

        ind = np.random.choice(vectors.shape[0], p=probabilities)
        chosen_indexes.append(ind)
        centroids.append(vectors[ind].tolist())

    return centroids, chosen_indexes


if __name__ == '__main__':
    main()
