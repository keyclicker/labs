import { createSlice, createAsyncThunk } from '@reduxjs/toolkit'
import { client } from '../api/client'

const initialState = {
  courses: [],
  status: 'idle',
  error: null,
}

export const fetchCourses = createAsyncThunk('courses/fetchCourses', 
  async () => {
    const response = await client.get('/fakeApi/courses')
    return response.data
  }
)

export const addNewCourse = createAsyncThunk('courses/addNewCourse',
  async (initialCourse) => {
    const response = await client.post('/fakeApi/courses', initialCourse)
    return response.data
  }
)

const coursesSlice = createSlice({
  name: 'courses',
  initialState,
  reducers: {
    userEnrolled(state, action) {
      const { courseId, reaction } = action.payload
      const existingCourse = state.courses.find((course) => course.id === courseId)
      if (existingCourse) {
        existingCourse.reactions[reaction]++
      }
    },
    courseUpdated(state, action) {
      const { id, title, content } = action.payload
      const existingCourse = state.courses.find((course) => course.id === id)
      if (existingCourse) {
        existingCourse.title = title
        existingCourse.content = content
      }
    },
  },
  extraReducers(builder) {
    builder
      .addCase(fetchCourses.pending, (state, action) => {
        state.status = 'loading'
      })
      .addCase(fetchCourses.fulfilled, (state, action) => {
        state.status = 'succeeded'
        // Add any fetched courses to the array
        state.courses = state.courses.concat(action.payload)
      })
      .addCase(fetchCourses.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
      })
      .addCase(addNewCourse.fulfilled, (state, action) => {
        state.courses.push(action.payload)
      })
  },
})

export const { courseAdded, courseUpdated, userEnrolled } = coursesSlice.actions

export default coursesSlice.reducer


// Selectors

export const selectAllCourses = (state) => state.courses.courses
export const selectCourseById = (state, courseId) =>
  state.courses.courses.find((course) => course.id === courseId)
