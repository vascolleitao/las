<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/vascolleitao/las">
    <img src="docs/images/logo/linkedin_banner_image_2.png" alt="Logo">
  </a>

<h3 align="center">LAS - Layered Algorithmic Skeletons</h3>

  <p align="center">
    LAS is an Algorithmic Skeleton Library with multiple layers of parallelization 
    <br />
    <a href="https://vascolleitao.github.io/las"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/vascolleitao/las">View Demo</a>
    ·
    <a href="https://github.com/vascolleitao/las/issues">Report Bug</a>
    ·
    <a href="https://github.com/vascolleitao/las/issues">Request Feature</a>
  </p>
</div>




<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li>
      <a href="#usage">Usage</a>
      <ul>
        <li><a href="#map">Map</a></li>   
        <li><a href="#reduce">Reduce</a></li>    
        <li><a href="#fusion">Fusion</a></li>      
        <li><a href="#filter">Filter</a></li>      
        <li><a href="#adapter-zip">Adapter Zip</a></li>        
        <li><a href="#adapter-index">Adapter Index</a></li>          
        <li><a href="#adapter-dummy">Adapter Dummy</a></li>          
        <li><a href="#omp-layer">OMP layer</a></li>          
      </ul>
    </li>
    <li><a href="#architecture">Architecture</a></li>
    <li><a href="#benchmark">Benchmark</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

LAS aspires to be a user-friendly library. This is accomplished by encapsulating all parallel functionality within the skeletons, removing the requirement for the user to understand or code anything about parallelization. The user simply needs to understand the skeletons' semantics.

Because the parallelization layers are coupled at compile time using inheritance and templates, LAS is capable of obtaining good performance. The library may also activate and deactivate certain layers at compile time, allowing the skeletons to be implemented on a variety of hardware architectures.

Multiple layers can be activated at the same time using LAS. This allows for hybrid levels of parallelization, such as OpenMP and MPI (albeit not yet!). As a result, LAS is a highly adaptable and portable algorithmic library.

LAS began as a master's thesis entitled "Padrões arquitecturais e de desenho para aplicações paralelas" (Architectural and Design Patterns for parallel applications) oriented by Prof. Dr. João Luís Ferreira Sobral. The dissertation's goal was to improve the architecture of HPC/parallel applications. LAS is an algorithmic skeleton library that uses numerous layers of parallelization to implement skeletons. This is a continuation of the original private project, which is currently in development.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may set up LAS locally.
By cloning a local copy and running the following simple example steps.

### Prerequisites

The prerequisite to install the library are: 
* C++ compiler with standard C++20

Depending on the parallelization layer, you may also need:
* OpenMP 

### Installation

1. Clone the repo
    ```sh
    git clone https://github.com/vascolleitao/las.git
    ```
2. Building
    ```sh
    cmake -B build -S las
    cmake --build build
    ```
3. Testing
    ```sh
    ctest --ctest-dir build
    ```
4. Installing
    ```sh
    cmake --install build \
          --prefix <INSTALL-DIR> 
    ```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

As explained above LAS has a layered architecture that permits its utilization wth the three following modes of utilization:
 - Default: only uses the sequential layer;
 - Static: uses the layers specified by de user at compile time by passing compile definitions;
 - Dynamic: compiling all the layers and choses the and choses the best one for a specific collection and skeleton. 

Each one of this modes is chosen at compile time by linking the executable with the respectively library
las, *las_static_layers* or *las_dynamic_layers*. The linkages with static layers also needs to link it with the specific layers (e.g., *las_cpu_layer* and *las_omp_layer*.

Next, you can see a various examples of the utilization of skeletons.


### Map

An example of using the map skeleton

Here is a simple example of incrementing all elements of a collection:

```cpp
std::vector<int> vec(1000);
vec >>= las::map(inc());
```

### Reduce

An example of using the reduce skeleton

This example shows how to sum all the elements of one collection.

```cpp
std::vector<int> vec{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
auto [sum] = vec >>= las::reduce(std::plus<int>());
```

### Fusion

Fusion multiple skeletons together

This example shows the fusion of two reduces. This operation returns a tuple, the first element corresponds to the result of the first reduce and the second element two the second reduce fused.

```cpp
std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
auto [min, max] = vec
  >>= las::reduce(las::min<int>())
  >>= las::reduce(las::max<int>());
```

Note that in this example, the first reduce is applied to the original collection and the second reduce is applied after computing the "complex_computation" on all elements of the collection. But both reduces are computed with only one loop, like lazy evaluation.

```cpp
std::vector<int> vec(100);
auto [sum_before_map, sum_after_map] = vec
  >>= las::reduce(std::plus<int>())
  >>= las::map(complex_computation())
  >>= las::reduce(std::plus<int>());
```

### Filter

In this example, a filter is used to erase the even numbers of a collection, by applying the skeleton map with the functor clear to the filtered ones. 

```cpp
std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
vec >>= las::filter(even())
    >>= las::map(clear());
```
### Adapter Zip

Adapting to allow the iteration of multiple collections simultaneously.
This example computes the multiplication point wise of two vectors *vx* and*vy* and storing the resulting vector on *vz*
```cpp
las::zip(vx, vy, vr) 
  >>= las::map(
    [](const auto& x, const auto& y, auto& r){ r = x*y;});
```

### Adapter Index

Iterating with indexes

This example shows how to initialize  the elements of a vector of the same position index.

```cpp
las::index(vec) >>= las::map([](int i, auto& v){ v[i] = i };);
```

### Adapter Dummy

Example of sharing variables between skeletons

Note that the dummy variable is not a collections but is treated as one. Using shared memory parallelization in example results in having one copy of this variable in every thread.

```cpp
pow = [](const int& x, int& d){ d = x*x };
las::zip(std::span(1,100), las::dummy<int>())
  >>= las::map(pow)
  >>= las::reduce(sum()) ;
```

### OMP layer

Using the map skeleton with threads

Here is a simple example initializing each element with the number of the corresponding thread.
This is not recommended since this way this code will only compile with the OMP layer, making it less portable.

```cpp
std::vector<int> vec(1000);
auto thread_num = [](auto& i) { i = omp_get_thread_num(); };
vec >>= las::map(thread_num);
```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Architecture -->
## Architecture

_For more examples, please refer to the [Documentation](https://vascolleitao.github.io/las)_
<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Benchmark -->
## Benchmark

The library was benchmark with three different applications: axpy, k-means and matrix multiplication.
The three problems have different complexities, being the fist one linear, quadratic an the and the last one is an iterative heuristic solution to the k-means problem, where the skeletons are used multiple times by iteration. In the following plots you can se the comparison of two examples of LAS shared memory (c++11 and omp threads) with a pure omp example.

The axpy problem is simply multiplying a vector by a scalar and summing the result with other vector, point wise.
The three version have similar speed ups. Although for smaller inputs the c++11 layer has better performance than OMP (not seen in these plots).

As it was expected the matrix multiplication has a good speedups due to being more computation intensive by element and the difference between using pure omp or the more simple skeletons approach is negligible. 

In the k-means problem as can be seen in the plot the speedup of which can be, at least partially, by being the fusion of multiple reduces, this makes LAS use multiple barriers to synchronize the threads instead of just once. With the LAS using the c++11 threads layer this problem didn't ocurred because the fusion was made manually.

<style>
  .div-speedup-plots { background-color: #FFFFFF }
</style>
<div class="div-speedup-plots">

<p float="left">
  <img src="docs/images/speedup/axpy.svg" width="32%" />
  <img src="docs/images/speedup/matrix_multiplication.svg" width="32%" />
  <img src="docs/images/speedup/kmeans.svg" width="32%" /> 
</p>

</div>

Note that, the use of the LAS library with only the sequential layer had the same performance as implementing them directly.

_For more examples, please refer to the [Documentation](https://vascolleitao.github.io/las)_
<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- Skeletons
    - [X] Map
    - [X] Reduce
    - [X] Fusion
    - [X] Filter
- Adapters
    - [X] Simple
    - [X] Index
    - [X] Zip
    - [ ] Reverse
- Parallelization
    - [X] Shared memory layer
        - [X] OMP 
        - [X] C++11 threads 
        - [ ] TBB 
    - [ ] Distributed memory layer
        - [ ] MPI 
    - [ ] GPU layer
        - [ ] CUDA 
        - [ ] OpenCL 

See the [open issues](https://github.com/vascolleitao/las/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the GPLv3 License.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Vasco Leitão - [@vascolleitao](https://twitter.com/vascolleitao) - vascolleitao@gmail.com

Project Link: [https://github.com/vascolleitao/las](https://github.com/vascolleitao/las)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
<!-- [contributors-shield]: https://img.shields.io/github/contributors/vascolleitao/las.svg?style=for-the-badge -->
[contributors-shield]: https://img.shields.io/github/contributors/vascolleitao/las.svg?style=for-the-badge
[contributors-url]: https://github.com/vascolleitao/las/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/vascolleitao/las.svg?style=for-the-badge
[forks-url]: https://github.com/vascolleitao/las/network/members
[stars-shield]: https://img.shields.io/github/stars/vascolleitao/las.svg?style=for-the-badge
[stars-url]: https://github.com/vascolleitao/las/stargazers
[issues-shield]: https://img.shields.io/github/issues/vascolleitao/las.svg?style=for-the-badge
[issues-url]: https://github.com/vascolleitao/las/issues
[license-shield]: https://img.shields.io/github/license/vascolleitao/las.svg?style=for-the-badge
[license-url]: https://github.com/vascolleitao/las/blob/master/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/vascolleitao
