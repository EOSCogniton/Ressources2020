import numpy as np

def f89(C,S):
    """
    Pacejka simplest function ('89): [Y] = f89(C, S)
    :param C: coefficient array from fit result
    :param S: SA or SL array from tire data test
    :return: fonction FY, FX ou MZ evaluated at S points
    """
    return C[0]*np.sin(C[1]*np.arctan(C[2]*(S-C[4])-C[3]*(C[2]*(S-C[4])-np.arctan(C[2]*(S-C[4]))))) + C[5]
              
if __name__ == '__main__':
    import matplotlib.pyplot as plt
    import matplotlib.ticker as ticker
    
    # FIGURE
    fig, ax = plt.subplots()
    fig.suptitle('title')
    
    # x - label 
    ax.set_xlabel("SA")
    ax.xaxis.set_major_locator(ticker.MultipleLocator(2))
    #ax.xaxis.set_minor_locator(ticker.MultipleLocator(1))
    
    # y - label
    ax.set_ylabel('Fy')
    #ax.yaxis.set_major_locator(ticker.MultipleLocator(0.5))
    #ax.xaxis.set_minor_locator(ticker.MultipleLocator(1))
    
    Fy = f89(coeff_Fy, SA)
    plt.plot(SA, Fy, '.-')