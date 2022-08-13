#include <cstdlib>
#include "archlab.hpp"
#include <unistd.h>
#include"omp.h"
#include"papi.h"
#include<algorithm>
#include<cstdint>
#include<unordered_set>
#include<map>
#include"function_map.hpp"



#define START_C extern "C" { // this just hides the braces from the editor, so it won't try to indent everything.
#define END_C  }


START_C
bool binarySearh(uint64_t a, uint64_t *search_space,  uint32_t l, uint32_t r){
        if( l > r ){
            return false;
        }else{
            uint32_t mid = (r+l)/2;
            if( a == search_space[mid]){
                return true;
            }else if(a > search_space[mid]){
                return binarySearh(a, search_space, mid+1, r);
            }else{
                return binarySearh(a, search_space, l, mid-1);
            }
        }
}

/*bool binarySearh(uint64_t a, uint64_t *search_space,  uint32_t l, uint32_t r){
        while( l == r ){
            uint32_t mid = (r+l)/2;
            if( a == search_space[mid] ){
                return true;
            }else if(a > search_space[mid]){
                l = mid + 1;
            }else{
                r = mid -1;
            }
        }
        return false;
}*/



uint64_t sum_of_locations_solution(uint64_t *search_space, uint32_t search_space_size, uint64_t* queries, uint32_t query_count)
{
        std::sort(search_space, &search_space[search_space_size]);
        uint32_t r = 0;
        uint64_t min = search_space[0];
        uint64_t max = search_space[search_space_size - 1];
        std::map<uint64_t, bool> myMap;
        for(uint32_t i = 0; i < query_count; i++) {
            std::map<uint64_t,bool>::const_iterator it = myMap.find (queries[i]);
            if(it != myMap.end()){
                if(it->second == true){
                     r += i;
                     continue;
                }else{
                     continue;
                }
            }
            if( queries[i] < min ){
                myMap[queries[i]] = false;
                continue;
            }
            if( queries[i] > max ){
                myMap[queries[i]] = false;
                continue;
            }
            if(binarySearh(queries[i],search_space, 0 , search_space_size-1)){
                myMap[queries[i]] = true;
                r += i;
            }
        }
	return r;
}


/*{
    std::unordered_set<uint64_t> mySet;
    uint64_t max  = -1000;
    uint64_t min  = 1000;
    for(uint32_t j = 0; j < search_space_size; j++){
        mySet.insert(search_space[j]);
        if(search_space[j] > max){
            max = search_space[j];
        }
        if(search_space[j] < min){
            min = search_space[j];
        }
    }
    uint32_t r = 0;
	for(uint32_t i = 0; i < query_count; i++) {
        if( queries[i] < min ){
            continue;
        }
        if(queries[i] > max){
            continue;
        }
        std::unordered_set<uint64_t>::const_iterator it = mySet.find (queries[i]);
        if ( it != mySet.end() ){
            r += i;
        }
	}
	return r;
}*/




// hello

FUNCTION("sum_impl", sum_of_locations_solution);

END_C
