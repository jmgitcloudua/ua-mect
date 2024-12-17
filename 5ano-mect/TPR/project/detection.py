import numpy as np

from sklearn.preprocessing import StandardScaler, MaxAbsScaler, RobustScaler
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix, ConfusionMatrixDisplay
from sklearn.decomposition import PCA

from sklearn.ensemble import IsolationForest
from sklearn.neighbors import LocalOutlierFactor
from sklearn.svm import OneClassSVM


normal_user_features = np.vstack( (np.loadtxt('data/bot_user_0_features.txt'), np.loadtxt('data/bot_user_1_features.txt'), np.loadtxt('data/bot_user_2_features.txt')) )
print(f'Loaded normal user features: ({normal_user_features.shape[0]}, {normal_user_features.shape[1]})')

attacker_0_features = np.loadtxt('data/bot_attacker_0_0_features.txt')
print(f'Loaded attacker 0 features: ({attacker_0_features.shape[0]}, {attacker_0_features.shape[1]})')

attacker_1_features = np.loadtxt('data/bot_attacker_1_0_features.txt')
print(f'Loaded attacker 1 features: ({attacker_1_features.shape[0]}, {attacker_1_features.shape[1]})')

normal_user_features[np.isnan(normal_user_features)] = -1
attacker_0_features[np.isnan(attacker_0_features)] = -1
attacker_1_features[np.isnan(attacker_1_features)] = -1


TRAIN_PERCENTAGE = 75

np.random.shuffle(normal_user_features) 

normal_train_split_index = int((normal_user_features.shape[0] * (TRAIN_PERCENTAGE / 100)))

normal_train_features = normal_user_features[:normal_train_split_index, :]
normal_test_features = normal_user_features[normal_train_split_index: , :]

test_train_features = np.vstack( (normal_test_features, attacker_0_features, attacker_1_features ) )
test_train_labels = np.hstack( (np.ones(normal_test_features.shape[0]), np.ones(attacker_0_features.shape[0]) * -1, np.ones(attacker_1_features.shape[0]) * -1) )

print(f'Train data is ({normal_train_features.shape[0]}, {normal_train_features.shape[1]})')
print(f'Test data is ({test_train_features.shape[0]}, {test_train_features.shape[1]})')

scaler = MaxAbsScaler().fit(normal_train_features)
normal_train_features = scaler.transform(normal_train_features)
test_train_features = scaler.transform(test_train_features)

local_outlier_factor = LocalOutlierFactor(n_neighbors=20, algorithm='kd_tree', leaf_size=50, metric='minkowski', p=2, metric_params=None, contamination=0.001, novelty=True, n_jobs=3)
local_outlier_factor.fit(normal_train_features)
print(f'LocalOutlierFactor fit done')

isolation_forest = IsolationForest(n_estimators=100, max_samples='auto', contamination=0.001, max_features=1.0, bootstrap=False, n_jobs=3, random_state=None, verbose=0, warm_start=False)
isolation_forest.fit(normal_train_features)
print(f'IsolationForest fit done')

oc_svm = OneClassSVM(kernel='sigmoid', degree=5, gamma=3.0, coef0=0.5, tol=0.0001, nu=0.001, shrinking=True, cache_size=1000, verbose=False, max_iter=-1)
oc_svm.fit(normal_train_features)
print(f'OneClassSVM fit done')

lof_predicted_labels = local_outlier_factor.predict(test_train_features)
isf_predicted_labels = isolation_forest.predict(test_train_features)
oc_svm_predicted_labels = oc_svm.predict(test_train_features)

methods = {'LocalOutlierFactor': lof_predicted_labels, 'IsolationForest': isf_predicted_labels, 'OneClassSVM': oc_svm_predicted_labels}

np.set_printoptions(suppress = True)

'''
  print("-- Analysis of Isolation Forest --")
    print("True Positives: {:>4}, False Negatives: {:>4}".format(tp, fn))
    print("True Negatives: {:>4}, False Positives: {:>4}".format(tn, fp))
    print("")
    print("{:<37}{:>6}".format("Accuracy (%): ", str(round(ac, 2))))
    print("{:<37}{:>6}".format("Precision (%): ", str(round(pr, 2))))
    print("{:<37}{:>6}".format("Recall (%): ", str(round(rec, 2))))
    print("{:<37}{:>6}".format("F1-Score: ", str(round(sc, 2))))
    print("-------------------------------------------\n")

'''

print("-- Analysis of Local Outlier Factor --")
print("{:<37}{:>6}".format("Accuracy (%): ", accuracy_score(test_train_labels, lof_predicted_labels)))
print("{:<37}{:>6}".format("Precision (%): ", precision_score(test_train_labels, lof_predicted_labels, average="micro")))
print("{:<37}{:>6}".format("Recall (%): ", recall_score(test_train_labels, lof_predicted_labels, average="micro")))
print("{:<37}{:>6}".format("F1-Score: ", f1_score(test_train_labels, lof_predicted_labels, average="micro")))
print("-------------------------------------------\n")


for method_name, predicted_labels in methods.items():
    print(f'Accuracy: \n{accuracy_score(test_train_labels, predicted_labels)}')
    print(f'-----------------------------------')
    # print(f'Precision: \n{precision_score(test_train_labels, predicted_labels, average="micro")}')
    # print(f'-----------------------------------')
    # print(f'Recall: \n{recall_score(test_train_labels, predicted_labels, average="micro")}')
    # print(f'-----------------------------------')
    # print(f'F-1: \n{f1_score(test_train_labels, predicted_labels, average="micro")}')
    # print(f'-----------------------------------')
    print(f'Confusion matrix: \n{confusion_matrix(test_train_labels, predicted_labels)}')
    print(f'-----------------------------------')


import matplotlib.pyplot as plt
from sklearn.manifold import TSNE
from sklearn.inspection import DecisionBoundaryDisplay

train_predict_features = np.vstack( (normal_user_features, attacker_0_features, attacker_1_features) )
train_predict_features = MaxAbsScaler().fit_transform(train_predict_features)

#train_predict_labels = np.hstack( (np.zeros(normal_user_features.shape[0]), np.ones(attacker_1_features.shape[0])) )

pca = PCA(n_components=2)
tsne = TSNE(n_components=2)

X_pca = pca.fit_transform(train_predict_features)
X_tsne = tsne.fit_transform(train_predict_features)

colors = ['green'] * normal_user_features.shape[0] + ['red'] * attacker_0_features.shape[0] + ['yellow'] * attacker_1_features.shape[0]



# plt.scatter(X_pca[: , 0], X_pca[:, 1], color=colors)
# plt.show()

local_outlier_factor = LocalOutlierFactor(n_neighbors=20, algorithm='kd_tree', leaf_size=50, metric='minkowski', p=2, metric_params=None, contamination=0.001, novelty=True, n_jobs=3)
local_outlier_factor.fit(X_tsne[:normal_user_features.shape[0], :])

ax = plt.subplot(111)

# DecisionBoundaryDisplay.from_estimator(
#     local_outlier_factor, X_tsne, cmap=plt.cm.RdBu, alpha=0.8, ax=ax, eps=0.5
# )

plt.scatter(X_tsne[: , 0], X_tsne[:, 1], color=colors)
plt.show()