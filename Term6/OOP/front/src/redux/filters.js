import { createSlice } from '@reduxjs/toolkit'

const initialState = {
  query: '',
  userRelated: false, 
}

const filtersSlice = createSlice({
  name: 'filters',
  initialState,
  reducers: {
    queryChanged: (state, action) => {
      state.query = action.payload
    },
    userRelatedChanged: (state, action) => {
      state.userRelated = action.payload
    }
  },
})

export const { queryChanged, userRelatedChanged } = coursesSlice.actions

export default coursesSlice.reducer


// Selectors

export const selectQuery = (state) => state.filters.query
export const selectUserRelated = (state) => state.filters.userRelated
