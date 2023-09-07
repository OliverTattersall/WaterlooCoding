import pandas as pd

# s = [1,2,3]

# var = pd.Series(s)

# print(var)

# print(var[0])


# weather = {"mon":25, "tues":21}
# var = pd.Series(weather)

# print(var)
# print(var['mon'])


''' data = {'age':[25,32,47],
        'weight' : [137,153, 119],
        'height' : [120, 180, 160]
        }

df = pd.DataFrame(data)
print(df)
print(df.loc[0]) #get row
print(df['age']) # get column
# print(df.loc[[0,1]]) # get multiple rows
print(df.loc[0:1]) # another way
# print(df.loc[[0:1], ['age', 'weight']]) # figure out how to do this thing

print(df.iloc[0:3]) '''


df = pd.read_csv("iris.csv")
# print(df.isnull())

# print(df.dropna().to_string())

# df['SepalLengthCm'].fillna("DSC", inplace=True) 
# df.dropna(subset=['SepalLengthCm'], inplace=True)

mean = df['SepalLengthCm'].mean()

df['SepalLengthCm'].fillna(mean, inplace=True)


print(df)

