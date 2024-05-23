# import libraries
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

# Pick constants
alpha = 15                   # Gravity
beta  = 1                   # Centrifugal
alpha = beta = float(input())

r = np.linspace(0.01,1,100)    # Define grid

# Define Potential Energy Functions
Ugr = -alpha/r                 # Gravity
Ucg = beta/(2.0*r**2)          # Centrifugal
Uef = Ugr + Ucg                # Effective

# Plot of 3 Potential Energy Functions

# plt.plot(r, Ugr,'--b',label="gravity", linewidth=2)
# plt.plot(r, Ucg,'--r',label="centrifugal", linewidth=2)
# plt.plot(r, Uef,'-g',label="effective", linewidth=2)
# plt.ylim([-300,200])
# plt.legend(loc='best')
# plt.show()


# plt.plot(r, Uef,'-g',label="effective",linewidth=2)
# plt.plot(r, 100+0*r,'--r', label="E>0")
# plt.plot(r,-100+0*r,'--b', label="E<0")
# plt.grid('on')
# plt.ylim([-300,200])
# plt.legend(loc='best')
# plt.show()

# Define the RHS of the Two-Body Problem

def rhs(Y,t,alpha,beta):
    phi, r, v = Y
    return np.sqrt(beta)/r**2, v, -alpha/r**2 + beta/r**3

# Time range
tt = np.linspace(0,2.0,1001)

# Initial conditions
# phi_0, r_0, v_0
y_init = [0, 1, float(input())]

# Parameters
#alpha = 15.0
#beta  = 1.0

# Find Solutions
soln = odeint(rhs, y_init, tt, args=(alpha, beta,))
phi,r,v = soln[:,0], soln[:,1], soln[:,2]

E = 0.5*v**2 + 0.5*beta/r**2 - alpha/r

print("Initial Energy = ", E[0])
print("Final Energy   = ", E[-1])
print("Relative error = ", (E[0]- E[-1])/E[0])


# plt.plot(tt,r, '-b',label='r')
# plt.title('Two-Body Problem')
# plt.xlabel('Time')
# plt.ylabel('Radius')
# plt.show()

# Translate solution to Cartesian Coordinates

x = r*np.cos(phi)
y = r*np.sin(phi)

plt.plot(x,y,label="Path", linewidth=2)
plt.plot(0.0,0.0,'or',label="CM",markersize=10)
plt.plot(x[0],y[0],'vg',label="Initial",markersize=10)
plt.plot(x[-1],y[-1],'^r',label="Final",markersize=10)
plt.legend(loc='best')
# plt.title((input()+"IC's: phi: {}, r_0: {}, v_0: {}, alpha: {}, beta: {}").format(y_init[0], y_init[1], y_init[2], alpha, beta) )
plt.show()
# plt.savefig(input())
