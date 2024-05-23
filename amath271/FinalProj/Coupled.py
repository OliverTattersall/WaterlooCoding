import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from random import random





k_bridge = 1


k = 80
m = 10
g = 1
l = 0.5

def rhs(r, t):
    return [r[1], g - (k/m)*r[0]]

# mt^2y'' + 2mty' + ky = mt^2g
# my'' + ky = mg

time = np.arange(0, 5, 1e-3)

# p, v = odeint(rhs, [1, 0], time).T
# # print(p)

# plt.plot(time, p, 'orange', linewidth = 2)
# plt.xlabel('time (s)')
# plt.ylabel('position (cm)')
# plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
# plt.grid(True)
# plt.show()


endt = 10
time = np.arange(0, endt, 1e-3)
k = 50
# m = 10
m_0 = 10
# damping = 0
damping = 1
# g = 10


k_connectors = 20
coupledOscillators = 81
# coupledOscillators = 81
l = 0.1/coupledOscillators
T = endt/coupledOscillators

# [y_0, y'_0, y_1,y'_1, y_2, y'_2]

def F(y_i, y_o):
    return -k_connectors*(((y_i-y_o)**2+l*l)**(0.5)-l)*(y_i - y_o)/(((y_i-y_o)**2+l*l)**(0.5))

def m(t, y):
    # m_car = 1
    m_car = 1.4
    # m_car = 0.3
    # m_car = 0
    repeat = coupledOscillators
    m_extra = (m_car if (y*T)%repeat <= (t)%repeat and (t)%repeat <= ((y+1)*T)%repeat else 0)
    # if(m_extra != 0):
    #     print(y, t)
    return m_0 + m_extra
def m2(t,y):
    m_car = 0.7
    m_car = 1.4
    m_extra = 0
    repeat = 1
    # repeat = coupledOscillators
    if(((y-1)*T)%repeat <= (endt - t)%repeat and (endt - t)%repeat <= (y*T)%repeat ):
        m_extra = m_car
    if((y*T)%repeat <= (t)%repeat and (t)%repeat <= ((y+1)*T)%repeat):
        m_extra = m_car
    return m_0 + m_extra

def rhs2(r, t):
    res = []
    for i in range(len(r)):
        if(i%2 == 0):
            res.append(r[i + 1])
        else:
            if(i // 2 == 0  ):
                # res.append((1/m_0)*( m_0*g - k * r[i - 1] + F(r[i - 1], r[i+1])))
                res.append((1/m_0)*(-1*damping*r[i] + m_0*g - k * r[i - 1] + F( r[i - 1], m_0*g/k) + F(r[i - 1], r[i+1])))

            elif(i == len(r) - 1):
                # res.append((1/m_0)*(m_0*g - k * r[i - 1] + F(r[i - 1], r[i-3])))
                res.append((1/m_0)*(-1*damping*r[i] + m_0*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], m_0*g/k)))
            else:
                # print(i)
                res.append((1/m_0)*(-1*damping*r[i] + m_0*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], r[i+1])))
                # res.append((1/m_0)*(m_0*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], r[i+1])))

    return res

def rhs3(r, t):
    res = []
    for i in range(len(r)):
        if(i%2 == 0):
            res.append(r[i + 1])
        else:
            if(i // 2 == 0  ):
                res.append((1/m(t, i//2))*(-1*damping*r[i] + m(t, i//2)*g - k * r[i - 1] + F( r[i - 1], m_0*g/k) + F(r[i - 1], r[i+1])))
                # res.append((1/m(t, i//2))*(m(t, i//2)*g - k * r[i - 1] + F( r[i - 1], m_0*g/k) + F(r[i - 1], r[i+1])))
            elif(i == len(r) - 1):
                res.append((1/m(t, i//2))*(-1*damping*r[i] + m(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], m_0*g/k)))
                # res.append((1/m(t, i//2))*(m(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], m_0*g/k)))

            else:
                # print(i)
                res.append((1/m(t, i//2))*(-1*damping*r[i] + m(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], r[i+1])))
                # res.append((1/m(t, i//2))*(m(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], r[i+1])))
    return res

def rhs4(r, t):
    res = []
    for i in range(len(r)):
        if(i%2 == 0):
            res.append(r[i + 1])
        else:
            if(i // 2 == 0  ):
                res.append((1/m2(t, i//2))*(-1*damping*r[i] + m2(t, i//2)*g - k * r[i - 1] + F( r[i - 1], m_0*g/k) + F(r[i - 1], r[i+1])))
                # res.append((1/m(t, i//2))*(m(t, i//2)*g - k * r[i - 1] + F( r[i - 1], m_0*g/k) + F(r[i - 1], r[i+1])))
            elif(i == len(r) - 1):
                res.append((1/m2(t, i//2))*(-1*damping*r[i] + m2(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], m_0*g/k)))
                # res.append((1/m(t, i//2))*(m(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], m_0*g/k)))

            else:
                # print(i)
                res.append((1/m2(t, i//2))*(-1*damping*r[i] + m2(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], r[i+1])))
                # res.append((1/m(t, i//2))*(m(t, i//2)*g - k * r[i - 1] + F(r[i - 1], r[i-3]) + F(r[i-1], r[i+1])))


    # return [r[1], (1/m)*(m*g - k*r[0] + F(r[0], r[2])), r[3], (1/m)*(m*g - k * r[2] + F(r[2], r[0]) + F(r[2], r[4])) , r[5], (1/m)*(m*g - k * r[4] + F(r[4], r[2]))]
    return res

# ics = [0.005 + m*g/k, 0, m*g/k, 0, m*g/k -0.005, 0.2, 0.1, 0, 0.5, 0, 0, 0]
# ics = [m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0, m_0*g/k, 0]
rics = [( m_0*g/k + random()/200 - 0.005  if i%2 == 0 else 0) for i in range(coupledOscillators*2)]
neareqics = [( m_0*g/k + 0.005  if i%2 == 0 else 0) for i in range(coupledOscillators*2)]
ateqics = [( m_0*g/k  if i%2 == 0 else 0) for i in range(coupledOscillators*2)]
shift = np.array(ateqics)+0.005
def mapit(i):
    if(i == 0):
        return 1
    if(i == 1):
        return 0
    if (i == 2):
        return -1
    if (i == 3):
        return 0
# # ateqics = [( (((i//2) % 2)*-2 + 1)* 0.005 + m_0*g/k if i%2 == 0 else 0) for i in range(coupledOscillators*2)]
# ateqics = [( (mapit((i%8)//2))* 0.005 + m_0*g/k if i%2 == 0 else 0) for i in range(coupledOscillators*2)]
# print(ateqics)

# res = np.array(odeint(rhs3, shift, time))
# res = np.array(odeint(rhs3, ateqics , time))
res = np.array(odeint(rhs4, ateqics , time))
# res = np.array(odeint(rhs2, ateqics , time))
# res = np.array(odeint(rhs2, neareqics , time))
# res = np.array(odeint(rhs3, rics , time))
# print(res, len(res))
# coupledOscillators = 16

p = [res[:, 2*i] for i in range(coupledOscillators)]



# # plt.figure()
# plt.ylim((0.19,0.21))
# plt.xlabel("t")
# plt.ylabel("y")
# plt.title("Y vs t for Alternating y_i(0)")
# for i in range(coupledOscillators):
#     plt.plot(time, p[i])
#     plt.plot(time, [m_0*g/k for i in range(len(time))])
# # plt.savefig("AlternatingYvsT")
# plt.show()


spots = np.array(np.arange(0, len(time), len(time)/5), int)
# spots = [0, 2000, 5750, 8000]
# spots = [5000, 5250, 5500, 5750]
# spots = np.append(spots, 5750)
spots = np.append(spots, 7095)
spots.sort()
spots = np.append(spots, len(time) - 1)
# spots.append(len(time) - 1)
for i in range(len(spots)):
    x = 0
    xs = []
    ys = []
    
    for j in range(coupledOscillators):
        # print(p[j])
        xs.append(x + l)
        # print(max(p[j]), min(p[j]))
        ys.append(p[j][spots[i]])
        # plt.plot(x + l, p[j][spots[i]], '-')
        x+=l 
    # plt.figure()
    plt.xlim((0, 0.1))
    plt.ylim((0.175,0.225))
    plt.xlabel("x")
    plt.ylabel("y")
    # case = "RandomIC's"
    # case = "Starting at equilibrium "
    # case = "Damped oscillations with mass variance"
    # case = "No mass variance "
    case = "Alternating IC placement "
    # case = "Random IC's, damped"
    # case = "All same with shift "
    case = "Massing moving towards each other"
    plt.title("The bridge at time: " + str(spots[i]*endt/len(time)) + "s Situation: " + case)
    plt.plot(xs, ys)
    # plt.plot(xs, [m_0*g/k for i in range(len(xs))])
    # plt.plot(xs, [0.005+m_0*g/k for i in range(len(xs))])
    s = case + "Time " + str(spots[i]) + ".png"
    
    # s = "Damped Time " + str(spots[i]) + ".png"
    # plt.savefig(s)
    plt.show()

# plt.plot(time, p[coupledOscillators//2])
# plt.plot(time, p[coupledOscillators//2 + 1])
# plt.plot(time, p[coupledOscillators//2 - 1])
# plt.show()
t = []
pm = np.amax(p)
pmin = min(p[0])
for i in range(len(time)):
    for j in range(coupledOscillators):
        if(abs(p[j][i] - pm) <=0.0000001 ):
            t.append(i)

print(t)
print(endt/len(time))