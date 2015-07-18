import math
import sys

import numpy as np
import numpy.linalg
import pylab as py
import matplotlib.pyplot as plt

def create_figure(size, order):
    fig = py.figure(figsize=(10,10))
    nth = 'th'
    if order < 4:
        nth = ['st','nd','rd','th'][order-1]

    title = "%s point smoothing" % size
    title += ", %d%s degree polynomial" % (order, nth)

    fig.text(.5, .92, title,
             horizontalalignment='center')

def plot(t, plots , vel_1 , vel_pos):
    n = len(plots)

    for i in range(0,n):
        label, data = plots[i]

        plt = py.subplot(n, 1, i+1)
        plt.tick_params(labelsize=10)
        py.grid()
        py.xlim([t[0], t[-1]])
        py.ylabel(label)

        plt.plot(t, data)
        if i == 0 :
            plt.plot(t,vel_pos)
            plt.plot(t,vel_1)
            
    py.xlabel("Time")

def load(name):
    f = open(name)    
    dat = [map(float, x.split(' ')) for x in f]
    f.close()

    pos = [x[0] for x in dat]
    vel = [x[1] for x in dat]
    t  = [x[2] for x in dat]
    #for i in range(0, len(t)):
    #	t[i] = t[i] + t[i-1]

    return np.array(pos), np.array(vel), np.array(t)

def plot_results():

    pos, vel, t = load('out.txt')
    plots = [
        ["Velocity",     vel[1:]]
    ]
    create_figure(7, 2)
    vel_pos = [(pos[i+1]-pos[i])/(t[i+1]-t[i]) for i in range(len(pos)-1)]
    print len(t[1:]), len(vel_pos), len(vel[1:])
    plot(t[1:], plots , vel[1:], vel_pos)

if __name__ == '__main__':
    plot_results()
    py.show()    