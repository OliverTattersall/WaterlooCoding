import numpy as np
import scipy.integrate as si
import matplotlib.pyplot as plt

def flux_SHO_ode(t, y, omega, beta):
    """ Flux for the simple harmonic oscillator (SHO) """
    return np.array([y[1], - 2*beta*y[1] - np.sin(y[0])*omega**2])

N     = 200                            # Number of time steps - 1
omega = 1.0                            # Natural Frequency
beta  = 1.0                            # Damping
t0    = 0.0                            # initial time
T     = 20.0                           # Period of oscillation
dt    = T/N                            # Time step
times = np.linspace(t0, T, N)
t0    = times[0]

ic    = np.array([0, 1])            # choose the initial conditions



names = ["No Damping B = 0, w = 2", "Weak Damping B = 1, w = 2", "Strong Damping B = 4, w = 2", "Critical Damping B = 2, w = 2"]
vals = [(0, 2), (1, 2), (4, 2), (2, 2)]

name = "No Damping B = 0, w = 2"
for i in range(4):
    # Plot time-series of solution
    b, o = vals[i]
    y = si.solve_ivp(flux_SHO_ode,[t0,T], ic, t_eval=times, args=[o, b],\
                 method='RK45', vectorized=True, rtol=1e-6).y
    plt.figure()
    plt.plot(times, y[0,:], '-b', times, y[1,:], '-r', lw=4)
    plt.title(names[i])
    plt.xlabel('time')
    plt.ylabel('solution')
    plt.legend(['x', 'v'])
    plt.grid()
    plt.savefig(names[i])



# # Plot phase-space
# plt.figure()
# plt.plot(y[0,:], y[1,:], '-b', lw=4)
# plt.title('Solution in phase space')
# plt.xlabel('x')
# plt.ylabel('v')
# plt.grid()
# plt.savefig('PhaseSpace.png')

# # Compute energy and decay rate of energy
# E = 1/2*y[1,:]**2 + omega**2*(1 - np.cos(y[0,:]))
# p = np.polyfit(times, np.log(E), 1)

# print('Decay exponent is approximately ', p[0])
# print('Relative change in energy is = ', (E[-1] - E[0])/E[0])

for i in range(4):
    # Plot time-series of energy
    b, o = vals[i]
    y = si.solve_ivp(flux_SHO_ode,[t0,T], ic, t_eval=times, args=[o, b],\
                 method='RK45', vectorized=True, rtol=1e-6).y
    E = 1/2*(y[1,:]**2) + (o**2)*(1 - np.cos(y[0,:]))
    # print(E)
    p = np.polyfit(times, np.log(E), 1)
    print('Decay rate is ', p[0])
    
    plt.figure()
    plt.ylim([-0.2, E[0]+ 0.3])
    plt.plot(times, E, '-b', lw=4)
    plt.title(names[i] + " Energy")
    plt.xlabel('time')
    plt.ylabel('Energy(J)')
    # plt.legend(['E'])
    plt.grid()
    plt.savefig(names[i] + " Energy")



# b, o = vals[0]
# y = si.solve_ivp(flux_SHO_ode,[t0,T], ic, t_eval=times, args=[o, b],\
#                 method='RK45', vectorized=True, rtol=1e-6).y
# E = 1/2*(y[1,:]**2) + (o**2)*(1 - np.cos(y[0,:]))

# x = np.linspace(0, 20, 200)
# print(E)
# plt.close("all")
# plt.plot(x, E)
# plt.show()
