Genetic-Algorithm
==============
2022 SSHS R&E 
(김선웅, 이지후, 박세진, 정현우)

내용
--------
Genetic-Algorithm을 이용해 max-sum matching을 해결했습니다.
#### 1. 해의 표현
i번째 A가 j번째 B와 matching된다 하면, A[i] = j로 표현합니다.
즉 해 하나하나를 순열로 표현하게 됩니다.
#### 2. 적합도 함수
matching의 간선의 가중치 합을 적합도로 설정했습니다. 이 값을 최대화하는 것이 목적입니다.
#### 3. 선택 연산
2개씩 비교해 더 높은 적합도를 가진 해를 부모로 사용하는 토너먼트 기법을 사용했습니다.
#### 4. 교차 연산
일부는 부모의 유전자를 유지하고, 일부는 다시 섞어주는 방법을 사용했습니다.
#### 5. 변이 연산
유전자의 점마다 일정 확률로 '변경 유전자'로 지정하고, '변경 유전자'들을 다시 한번 섞어주는 연산을 수행합니다.
#### 6. 대치 연산
토너먼트 방식에서 패배한 유전자를 교차 연산을 통해 생성된 유전자로 교체합니다.
#### 7. 정지 조건 
일정 세대가 지난 후에 종료하는 방법을 사용합니다.
