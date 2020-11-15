#pragma once

#include <thread>
#include <list>

// thanks to: https://stackoverflow.com/questions/36246300/parallel-loops-in-c

namespace Lincpp
{
    namespace internal
    {
        template <typename TFunc>
        static void ParallelFor(unsigned start, unsigned end, TFunc func)
        {
            //internal loop
            auto internal_func = [&func](unsigned internal_start, unsigned segment_size) {
                for (unsigned j = internal_start; j < internal_start + segment_size; j++)
                    func(j);
            };

            //get number of threads
            unsigned number_threads_hint = std::thread::hardware_concurrency();
            unsigned number_threads = number_threads_hint == 0 ? 8 : (number_threads_hint);

            //calculate segments
            unsigned total_length = end - start;
            unsigned segment = total_length / number_threads;
            unsigned last_segment = segment + total_length % number_threads;

            //launch threads - parallel for
            auto threads = std::list<std::thread>();
            for (unsigned k = 0; k < number_threads - 1; ++k)
            {
                unsigned current_start = segment * k;
                threads.emplace_back(std::thread(internal_func, current_start, segment));
            }
            {
                unsigned current_start = segment * (number_threads - 1);
                threads.emplace_back(std::thread(internal_func, current_start, last_segment));
            }
            for (auto &th : threads)
                th.join();
        }
    } // namespace internal
} // namespace Lincpp
