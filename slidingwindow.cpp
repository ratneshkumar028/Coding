class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;

        int maxVal = 0;

        for(int i = 0; i <= n - k; i++) {

            
            if(i == 0) {
                maxVal = nums[i];
                for(int j = i; j < i + k; j++) {
                    if(nums[j] > maxVal)
                        maxVal = nums[j];
                }
            }
            else {
                
                if(maxVal != nums[i - 1]) {
                    if(nums[i + k - 1] > maxVal)
                        maxVal = nums[i + k - 1];
                }
                else {
                
                    maxVal = nums[i];
                    for(int j = i; j < i + k; j++) {
                        if(nums[j] > maxVal)
                            maxVal = nums[j];
                    }
                }
            }

            ans.push_back(maxVal);
        }

        return ans;
    }
};
